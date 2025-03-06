import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return render_template("quote.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        # Validate the form
        if len(symbol) == 0:
            return apology("Missin symbol")
        if shares == '' or int(shares) <= 0:
            return apology("Missing shares")
        # Search the quote
        result_quote = lookup(symbol)
        if result_quote == None:
            return apology("INVALID SYMBOL")

        # Verify if the user can afford or not
        user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        # before it is parsed
        price = float(result_quote["price"])
        total_price = int(shares) * price
        if int(user[0]["cash"]) < total_price:
            return apology(f"cant afford {result_quote["name"]}")

        # Process the purchase
        try:
            db.execute("INSERT INTO buys (symbol, shares, price, id_user) VALUES (?, ?, ?, ?)",
                       symbol, shares, price, session["user_id"])
        except Exception as e:
            return apology("Error during the transaction", e)
        # now update the cash of the user
        new_cash = round(float(user[0]["cash"]) - total_price, 2)
        try:
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, session["user_id"])
            return redirect("/")
        except Exception as e:
            return apology("Error updating cash", e)
    else:

        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")

        if (len(symbol) == 0):
            return apology("It was expected a Symbol")
        # Query the quote
        try:
             result_quote = lookup(symbol)
             if (result_quote):
                return render_template("quoted.html", result_quote=result_quote)
             else:
                 return apology("Quote Not Found")

        except Exception as e:
            return apology(f"Error to quering the quote {symbol}", e)


    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":

        if "user_id" not in session:
            session["user_id"] = None
        if session["user_id"]:
            # if exist active sesion redirect to principal page
            return redirect("/")
        return render_template("login.html", type='register')
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        password_confirm = request.form.get("password-confirm")
        # verify the passwords
        if password != password_confirm:
            return apology("passwords don't match")
        # validate if the current user not exist in the db
        user_match = db.execute("SELECT username FROM users WHERE username = ?", username)
        # Note: this result query will be an array, altought it expect a single result
        # that's why it's necessary to access by index
        if user_match and user_match[0]["username"] == username:
            return apology(f"The current user {username} already exist!")
        # encrypt the password before add to database
        try:

            encrypt_password = generate_password_hash(password)
        except Exception as e:
            return apology(f"Error to encrypt the password", e)
        # add the user
        try:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, encrypt_password)
            return redirect("/")
        except Exception as e:

            return apology(f"Error to create the User", e)


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")

