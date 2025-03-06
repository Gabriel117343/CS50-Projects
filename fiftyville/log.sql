-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find crime scene description
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND stree = 'Humphrey Street';

-- Find interviews in that date
SELECT * FROM interviews
WHERE year = 2024 AND month = 7
AND day = 28;

-- Find the airport in 'Fiftyville' (id: 8)
SELECT * FROM aiports WHERE city = 'Fiftyville';

-- Find the earliest flight in the next day
SELECT * FROM flights WHERE year = 2024 AND month = 7 AND day = 29 ORDER BY hour DESC;

-- Find the destination (result: 'New York City)
SELECT * FROM airports WHERE id = 4;

-- Find the passport of the passengeres
SELECT * FROM passengers WHERE flight_id = 4;
-- Search people that board that flight

SELECT * FROM people WHERE passport_number IN (
    SELECT passport_number FROM passengers WHERE flight_id = 4

)

