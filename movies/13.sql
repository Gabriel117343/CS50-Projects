SELECT p.name
FROM people p
JOIN stars s ON p.id = s.person_id
JOIN movies m ON s.movie_id = m.id
WHERE m.id IN (
    SELECT s2.movie_id
    FROM stars s2
    JOIN people p2 ON s2.person_id = p2.id
    WHERE p2.name = 'Kevin Bacon' AND p2.birth = 1958
)
AND p.name != 'Kevin Bacon';
