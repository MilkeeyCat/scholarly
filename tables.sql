CREATE TABLE groups (
    id SERIAL PRIMARY KEY,
    name VARCHAR(64)
);

CREATE TABLE students (
    id SERIAL PRIMARY KEY,
    first_name VARCHAR(128),
    last_name VARCHAR(128),
    group_id INT REFERENCES groups(id) ON DELETE CASCADE,
    created_at TIMESTAMPTZ DEFAULT NOW()
);

CREATE TABLE subjects (
    id SERIAL PRIMARY KEY,
    name VARCHAR(128)
);

CREATE TABLE teachers (
    id SERIAL PRIMARY KEY,
    first_name VARCHAR(128),
    last_name VARCHAR(128),
    subject_id INT REFERENCES subjects(id) ON DELETE CASCADE,
    created_at TIMESTAMPTZ DEFAULT NOW()
);

CREATE TABLE estimates (
    id SERIAL PRIMARY KEY,
    student_id INT REFERENCES students(id) ON DELETE CASCADE,
    teacher_id INT REFERENCES teachers(id) ON DELETE CASCADE,
    estimation SMALLINT,
    created_at TIMESTAMPTZ DEFAULT NOW()
);


-- TEST DATA

INSERT INTO groups (name) VALUES
('kn'),
('mb'),
('foo');

INSERT INTO subjects (name) VALUES
('Mafs'),
('Chemistry'),
('Programming'),
('Numbers theory');

INSERT INTO teachers (first_name, last_name, subject_id) VALUES
('Seraphina', 'Blackwood', 1),
('Jasper', 'Frost', 3),
('Amara', 'Silverstone', 1),
('Daxton', 'Nightingale', 2),
('Lyra', 'Evergreen', 4);

INSERT INTO students (first_name, last_name, group_id) VALUES
('Orion', 'Hawthorne', 1),
('Nova', 'Raines', 2),
('Finnegan', 'Drake', 3),
('Lila', 'Starling', 1),
('Atticus', 'Stone', 2),
('Isadora', 'Moon', 3),
('Phoenix', 'Wilde', 1),
('Thalia', 'Ember', 2),
('Cassius', 'Rivers', 3),
('Aurora', 'Skyfern', 1);


INSERT INTO estimates (student_id, estimation, teacher_id) VALUES
(7, 1, 4),
(2, 3, 2),
(5, 4, 5),
(10, 2, 3),
(3, 5, 1),
(8, 2, 4),
(1, 1, 2),
(9, 4, 3),
(6, 3, 5),
(4, 5, 1),
(2, 2, 4),
(7, 5, 2),
(8, 1, 5),
(3, 3, 3),
(6, 4, 1),
(5, 2, 4),
(1, 1, 2),
(9, 5, 5),
(4, 3, 3),
(10, 4, 1),
(7, 2, 4),
(2, 4, 2),
(3, 3, 5),
(8, 1, 3),
(5, 5, 1),
(6, 2, 4),
(9, 3, 2),
(1, 4, 5),
(4, 1, 3),
(10, 5, 1);
