-- Keep a log of any SQL queries you execute as you solve the mystery.
-- first navigate to folder and open sqlite3 fiftyville.db

-- overview of the table and schema
.table
.schema

-- get description based on provided time and street name
-- All you know is that the theft took place on July 28, 2020 and that it took place on Chamberlin Street.
SELECT description FROM crime_scene_reports WHERE street = "Chamberlin Street" AND day = 28 AND month = 7 AND year = 2020;
-- findings
-- took place at 10:15am
-- Chamberlin Street courthouse
-- 3 interview with witness presence were conducted
-- transcripts mentioneds "courthouse"

-- search for interviews based on above info
SELECT * FROM interviews WHERE transcript LIKE "%courthouse%" AND day = 28 AND month = 7 AND year = 2020;
-- around 10min of theft,
-- this morning, withdrawing money at "Fifer Street"
-- when leaving, phone call for less than 1 minute
-- earliest flight out of Fiftyville next day - the accomplice purchase

-- 1: car leaving parking
SELECT * FROM courthouse_security_logs WHERE day = 28 AND month = 7 AND year = 2020 AND hour = 10 AND minute > 15 AND minute < 25;
-- ^ see all license plates
-- use license plate to find 10 potential theifs
SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE day = 28 AND month = 7 AND year = 2020 AND hour = 10 AND minute > 15 AND minute < 25);

-- 2: withdrawing from ATM
SELECT * FROM atm_transactions WHERE atm_location = "Fifer Street" AND day = 28 AND month = 7 AND year = 2020;
SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND day = 28 AND month = 7 AND year = 2020));

-- combine query 1 and 2
SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND day = 28 AND month = 7 AND year = 2020)) AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE day = 28 AND month = 7 AND year = 2020 AND hour = 10 AND minute > 15 AND minute < 25);
-- we have 4 suspects, who were in the courthouse at the time of the crime
-- and that withdrew money earlier that day:
-- id | name | phone_number | passport_number | license_plate
-- 396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
-- 467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
-- 514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
-- 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X

-- 3: thief phone calls
SELECT * FROM phone_calls WHERE caller IN (SELECT phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND day = 28 AND month = 7 AND year = 2020)) AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE day = 28 AND month = 7 AND year = 2020 AND hour = 10 AND minute > 15 AND minute < 25)) AND day = 28 AND month = 7 AND year = 2020 AND duration < 60;
-- we get 2 results:
-- caller (thief) | receiver (accomplice)
-- 233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7 | 28 | 45
-- 255 | (770) 555-1861 | (725) 555-3243 | 2020 | 7 | 28 | 49
SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE caller IN (SELECT phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND day = 28 AND month = 7 AND year = 2020)) AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE day = 28 AND month = 7 AND year = 2020 AND hour = 10 AND minute > 15 AND minute < 25)) AND day = 28 AND month = 7 AND year = 2020 AND duration < 60);
-- reciever / accomplice: Philip or Berthold
SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE caller IN (SELECT phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND day = 28 AND month = 7 AND year = 2020)) AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE day = 28 AND month = 7 AND year = 2020 AND hour = 10 AND minute > 15 AND minute < 25)) AND day = 28 AND month = 7 AND year = 2020 AND duration < 60);
-- caller / thief: Ernest or Russell

-- 4: earliset flight next day
SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id IN (SELECT id FROM airports WHERE full_name LIKE "%fiftyville%") ORDER BY hour LIMIT 1));

-- combingin all queries
SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE caller IN (SELECT phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND day = 28 AND month = 7 AND year = 2020)) AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE day = 28 AND month = 7 AND year = 2020 AND hour = 10 AND minute > 15 AND minute < 25)) AND day = 28 AND month = 7 AND year = 2020 AND duration < 60) AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id IN (SELECT id FROM airports WHERE full_name LIKE "%fiftyville%") ORDER BY hour LIMIT 1));
-- thief = Ernest

-- naming thief and accomlice based on phone call
SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE caller IN (SELECT people.phone_number FROM people WHERE people.phone_number IN (SELECT caller FROM phone_calls WHERE caller IN (SELECT phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND day = 28 AND month = 7 AND year = 2020)) AND people.license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE day = 28 AND month = 7 AND year = 2020 AND hour = 10 AND minute > 15 AND minute < 25)) AND day = 28 AND month = 7 AND year = 2020 AND duration < 60) AND people.passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id IN (SELECT id FROM airports WHERE full_name LIKE "%fiftyville%") ORDER BY hour LIMIT 1)))AND day = 28 AND month = 7 AND year = 2020 AND duration < 60);
SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE caller IN (SELECT people.phone_number FROM people WHERE people.phone_number IN (SELECT caller FROM phone_calls WHERE caller IN (SELECT phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND day = 28 AND month = 7 AND year = 2020)) AND people.license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE day = 28 AND month = 7 AND year = 2020 AND hour = 10 AND minute > 15 AND minute < 25)) AND day = 28 AND month = 7 AND year = 2020 AND duration < 60) AND people.passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id IN (SELECT id FROM airports WHERE full_name LIKE "%fiftyville%") ORDER BY hour LIMIT 1)))AND day = 28 AND month = 7 AND year = 2020 AND duration < 60);
-- accomplice = Berthold

-- finding the destination airport
SELECT full_name FROM airports WHERE id IN (SELECT destination_airport_id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id IN (SELECT id FROM airports WHERE full_name LIKE "%fiftyville%") ORDER BY hour LIMIT 1);
-- Heathrow Airport
