CREATE TABLE students (
    id SERIAL PRIMARY KEY,
    first_name VARCHAR(128),
    last_name VARCHAR(128),
    year SMALLINT,
    _group VARCHAR(4)
);

CREATE TABLE subjects (
    id SERIAL PRIMARY KEY,
    name VARCHAR(128)
);

CREATE TABLE teachers (
    id SERIAL PRIMARY KEY,
    first_name VARCHAR(128),
    last_name VARCHAR(128)
);

CREATE TABLE estimates (
    id SERIAL PRIMARY KEY,
    student_id INT REFERENCES students(id) ON DELETE CASCADE,
    subject_id INT REFERENCES subjects(id) ON DELETE CASCADE
);
