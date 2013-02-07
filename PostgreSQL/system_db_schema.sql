START TRANSACTION;

CREATE TABLE a23t_account (
    id                  SERIAL                      PRIMARY KEY,
    login_name          TEXT                        NOT NULL UNIQUE,
    real_name           TEXT                        NOT NULL,
    password_hash       TEXT                        NOT NULL,
    password_salt       TEXT                        NOT NULL,
    email               TEXT                        NOT NULL,
    account_disable     boolean                     NOT NULL
);
-- COMMENT ON TABLE a23t_account IS 'table have the values of webgui accounts.';
-- COMMENT ON COLUMN a23t_account.account_disable IS 'If set true than the account is disabled';


-- Default accound "admin" with password "admin". 
INSERT INTO a23t_account 
( 
    id,
    login_name, 
    real_name, 
    password_hash, 
    password_salt, 
    email, 
    account_disable 
) 
VALUES ( 
    1
    'admin',
    '',
    '43b732f80b0308a1c26114e42d377e2f',
    'fa37JncCHryDsbza',
    '',
    'FALSE'
);

CREATE TABLE a23t_roll (
    id              SERIAL    PRIMARY KEY,
    name            TEXT      NOT NULL UNIQUE,
    explanation     TEXT      NOT NULL
);
-- COMMENT ON TABLE a23t_rolls IS 'ACL rolls.';
-- Default accound "admin" with password "admin". 

-- Default rolls. 
INSERT INTO a23t_account 
( 
    id,
    name, 
    explanation
) 
VALUES ( 
    1,
    'admin',
    ''
); 

INSERT INTO a23t_account 
( 
    id,
    name, 
    explanation
) 
VALUES ( 
    2,
    'seeker',
    ''
);

INSERT INTO a23t_account 
( 
    id,
    name, 
    explanation
) 
VALUES ( 
    3,
    'provider',
    ''
);


CREATE TABLE a23t_account_rolls (
    id              SERIAL    PRIMARY KEY,
    account_id      INTEGER   NOT NULL,
    roll_id         INTEGER   NOT NULL,
    FOREIGN KEY  (account_id) REFERENCES a23t_account (id)
    FOREIGN KEY  (roll_id) REFERENCES a23t_roll (id)
);
-- COMMENT ON TABLE a23t_account_rolls IS 'Linking acconds with rolls.';

-- admin account get all rolls.
INSERT INTO a23t_account 
( 
    account_id, 
    roll_id
) 
VALUES ( 
    1,
    1
);

INSERT INTO a23t_account 
( 
    account_id, 
    roll_id
) 
VALUES ( 
    1,
    2
);

INSERT INTO a23t_account 
( 
    account_id, 
    roll_id
) 
VALUES ( 
    1,
    3
);

CREATE TABLE db_account (
    account_id      SERIAL    PRIMARY KEY,
    account_name    TEXT      NOT NULL UNIQUE,
    server_name     TEXT      NOT NULL,
    database_name   TEXT      NOT NULL,
    port_no         INTEGER   NOT NULL,
    db_encoding     TEXT      NOT NULL,
    db_user         Text      NOT NULL,
    db_password     TEXT      NOT NULL,
    db_sslmode      TEXT      NOT NULL,
    owner_id        INTEGER   NOT NULL,
    FOREIGN KEY  (account_id) REFERENCES a23t_account (id)
);
-- COMMENT ON TABLE db_account IS 'Variable postgressql accounds for crm data.';
-- COMMENT ON COLUMN db_account.account_id IS 'Link to a webgui user account.';

COMMIT;