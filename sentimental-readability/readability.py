
import cs50


def count_letters(text):
    count = 0
    for char in text:
        # if is character valid
        if char.isalpha():
            count += 1
    return count


def count_words(text):
    count = 1
    for char in text:
        if char == ' ':
            count += 1
    return count


def count_sentences(text):
    count = 0
    for char in text:
        if char in ['.', '!', '?']:
            count += 1
    return count


text = cs50.get_string("Text: ")
# count
letters = count_letters(text)
words = count_words(text)
sentences = count_sentences(text)

# calculate the values
L = (float(letters) / words) * 100
S = (float(sentences) / words) * 100
index = 0.0588 * L - 0.296 * S - 15.8
if (index < 1):
    print("Before Grade 1")
elif (index >= 16):
    print("Grade 16+")
else:
    print(f"Grade {round(index)}")
