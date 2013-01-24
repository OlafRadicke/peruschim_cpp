START TRANSACTION;

CREATE TABLE a23i_account (
    id                  SERIAL                      PRIMARY KEY,
    login_name          TEXT                        NOT NULL UNIQUE,
    real_name           TEXT                        NOT NULL,
    password_hash       TEXT                        NOT NULL,
    password_salt       TEXT                        NOT NULL,
    email               TEXT                        NOT NULL,
    account_disable     boolean                     NOT NULL
);
-- COMMENT ON TABLE a23i_account IS 'table have the values of webgui accounts.';
-- COMMENT ON COLUMN a23i_account.account_disable IS 'If set true than the account is disabled';

-- INSERT INTO a23i_account
-- (   
--     account_id,
--     login_name,
--     real_name,
--     password_hash,
--     password_salt,
--     email,
--     account_disable
-- ) VALUES
-- (
--     DEFAULT,
--     "admin",
--     "admin",
--     "",
--     "",
--     "artikel23i@localhost",
--     FALSE
-- );

CREATE TABLE a23i_db_account (
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
    FOREIGN KEY  (account_id) REFERENCES a23i_account (account_id)
);
-- COMMENT ON TABLE a23i_db_account IS 'Variable postgressql accounds for crm data.';
-- COMMENT ON COLUMN a23i_db_account.account_id IS 'Link to a webgui user account.';

COMMIT;