START TRANSACTION;

CREATE TABLE metadata (
    id                  SERIAL                      PRIMARY KEY,
    data_name           TEXT                        NOT NULL UNIQUE,
    data_parameter      TEXT                        NOT NULL,
    data_value          TEXT                        NOT NULL,
    data_description    TEXT                        NOT NULL
);
-- COMMENT ON TABLE metadata IS 'table have the values of meta data. For example the database table version.';
-- COMMENT ON COLUMN account.account_disable IS 'If set true than the account is disabled';

-- Insert table versions number.
INSERT INTO metadata
(
    data_name,
    data_parameter,
    data_value,
    data_description
)
VALUES (
    'tableversion',
    'alpha',
    '00001',
    'Namber of table version'
);

CREATE TABLE account (
    id                  SERIAL                      PRIMARY KEY,
    login_name          TEXT                        NOT NULL UNIQUE,
    real_name           TEXT                        NOT NULL,
    password_hash       TEXT                        NOT NULL,
    password_salt       TEXT                        NOT NULL,
    email               TEXT                        NOT NULL,
    account_disable     boolean                     NOT NULL
);
-- COMMENT ON TABLE account IS 'table have the values of webgui accounts.';
-- COMMENT ON COLUMN account.account_disable IS 'If set true than the account is disabled';


-- Default accound "admin" with password "admin".
INSERT INTO account
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
    1,
    'admin',
    '',
    '43b732f80b0308a1c26114e42d377e2f',
    'fa37JncCHryDsbza',
    '',
    'FALSE'
);

CREATE TABLE acl_roll (
    id              SERIAL    PRIMARY KEY,
    name            TEXT      NOT NULL UNIQUE,
    explanation     TEXT      NOT NULL
);
-- COMMENT ON TABLE acl_roll IS 'ACL rolls.';
-- Default accound "admin" with password "admin".

-- Default rolls.
INSERT INTO acl_roll
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

INSERT INTO acl_roll
(
    id,
    name,
    explanation
)
VALUES (
    2,
    'user',
    ''
);



CREATE TABLE account_acl_roll (
    id              SERIAL    PRIMARY KEY,
    account_id      BIGINT    NOT NULL,
    acl_roll_id     BIGINT    NOT NULL,
    FOREIGN KEY  (account_id) REFERENCES account (id),
    FOREIGN KEY  (acl_roll_id) REFERENCES acl_roll (id)
);
-- COMMENT ON TABLE account_acl_roll IS 'Linking acconds with rolls.';

-- admin account get all rolls.
INSERT INTO account_acl_roll
(
    account_id,
    acl_roll_id
)
VALUES (
    1,
    1
);

INSERT INTO account_acl_roll
(
    account_id,
    acl_roll_id
)
VALUES (
    1,
    2
);



CREATE TABLE edition (
    id              SERIAL    PRIMARY KEY,
    owner_id        BIGINT    NOT NULL,
    name            TEXT      NOT NULL,
    publishername   TEXT      NOT NULL,
    releasenumber   TEXT      NOT NULL,
    releasedate     TEXT      NOT NULL,
    releaseplace    TEXT      NOT NULL,
    FOREIGN KEY  (owner_id)   REFERENCES account (id)
);

-- Default value
INSERT INTO edition
(
    id,
    owner_id,
    name,
    publishername,
    releasenumber,
    releasedate,
    releaseplace
)
VALUES (
    0,
    1,
    'andere',
    '',
    '',
    '',
    ''
);

CREATE TABLE quote (
    id              SERIAL    PRIMARY KEY,
    series          TEXT      NOT NULL,
    title           TEXT      NOT NULL,
    chapter_begin   INTEGER   NOT NULL,
    sentence_begin  INTEGER   NOT NULL,
    chapter_end     INTEGER   NOT NULL,
    sentence_end    INTEGER   NOT NULL,
    quote_text      TEXT      NOT NULL,
    note            TEXT      NOT NULL,
    owner_id        BIGINT    NOT NULL,
    edition_id      BIGINT    NOT NULL,
    privatedata     BOOLEAN   NOT NULL,
    FOREIGN KEY  (owner_id)   REFERENCES account (id),
    FOREIGN KEY  (edition_id) REFERENCES edition (id)
);
-- COMMENT ON TABLE quote IS 'Data sets of bible quotes.';
-- COMMENT ON COLUMN quote.series IS 'Name of a book series like "Bible".';
-- COMMENT ON COLUMN quote.title IS 'Book title like "1. Mose".';
-- COMMENT ON COLUMN quote.chapter_begin IS 'Chaper of the begin of quote';
-- COMMENT ON COLUMN quote.owner IS 'Owner and author of this data set.';
-- COMMENT ON COLUMN quote.privatedata IS 'Is this value TRUE than the data set is private.';



CREATE TABLE quote_keyword (
    id              SERIAL    PRIMARY KEY,
    quote_id        BIGINT    NOT NULL,
    title           TEXT      NOT NULL,
    FOREIGN KEY  (quote_id)   REFERENCES quote (id)
);
-- COMMENT ON TABLE quote_keyword IS 'the key words of the quotes.';
-- COMMENT ON COLUMN quote_keyword.quote_id IS 'id from a quotes to like key word with quotes.';
-- COMMENT ON COLUMN quote_keyword.title IS 'key word title like "gebet".';


CREATE TABLE rss_feeds(
    id              SERIAL    PRIMARY KEY,
    title           TEXT      NOT NULL,
    linkurl         TEXT      NOT NULL,
    description     TEXT      NOT NULL,
    createtime      TIMESTAMP NOT NULL
);
-- COMMENT ON TABLE rss_feeds IS 'puplic rss feed items.';
-- COMMENT ON COLUMN rss_feeds.linkurl IS 'Linkt to artikle.';

CREATE TABLE rss_feeds_channel(
    id              SERIAL    PRIMARY KEY,
    channel_title   TEXT      NOT NULL,
    rss_feeds_id    BIGINT    NOT NULL,
    FOREIGN KEY  (rss_feeds_id)   REFERENCES rss_feeds (id)
);
-- COMMENT ON TABLE rss_feeds_channel IS 'the channels of a rss feed item.';
-- COMMENT ON COLUMN rss_feeds_channel.rss_feeds_id IS 'Linkt to rss feed item.';

CREATE TABLE account_trust (
    id                   SERIAL    PRIMARY KEY,
    trusted_account_id   BIGINT    NOT NULL,
    guarantor_id         BIGINT    NOT NULL,
    createtime           TIMESTAMP NOT NULL,
    FOREIGN KEY  (trusted_account_id)   REFERENCES account (id),
    FOREIGN KEY  (guarantor_id) REFERENCES edition (id)
);
-- COMMENT ON TABLE account_trust IS 'Links for user trust user.';
-- COMMENT ON COLUMN account_trust.trusted_account_id IS 'The account where we are in trust.';
-- COMMENT ON COLUMN account_trust.guarantor_id IS 'This account give the guarant.';


COMMIT;
