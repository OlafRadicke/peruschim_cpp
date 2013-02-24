
START TRANSACTION;

CREATE TABLE a23_activity (
    activity_id         integer                     NOT NULL,
    time_pressure       integer                     NOT NULL,
    priority            integer                     NOT NULL,
    alarm_time          timestamp without time zone,
    snooze_interval     bigint,
    delete_date         timestamp without time zone,
    title               text                        NOT NULL,
    note                text                        NOT NULL,
    CONSTRAINT activity_priority_check      CHECK (((priority > (-1)) AND (priority < 101))),
    CONSTRAINT activity_time_pressure_check CHECK (((time_pressure > (-1)) AND (time_pressure < 101)))
);

COMMENT ON TABLE a23_activity
IS 'Aktivitäten (TODOS) für den Workflow';
COMMENT ON COLUMN a23_activity.activity_id
IS 'ID der Aktivität';
COMMENT ON COLUMN a23_activity.time_pressure
IS 'Wert von 0 bis 100 % (0 ist wenig / 100 sehr dringlich)';
COMMENT ON COLUMN a23_activity.priority
IS 'Wert von 0 bis 100 % (0 unwichtig / 100 sehr wichtig ';
COMMENT ON COLUMN a23_activity.alarm_time
IS 'Zeitpunkt (Datum+Uhrzeit) zu dem erinnert werden soll';
COMMENT ON COLUMN a23_activity.snooze_interval
IS 'Erinnerungs-Intervall (wie ein Timer) in Ticks';
COMMENT ON COLUMN a23_activity.delete_date
IS 'Zeitstempel der Löschung der Aktivität';
COMMENT ON COLUMN a23_activity.title
IS 'Überschrift der Aktivität';
COMMENT ON COLUMN a23_activity.note
IS 'Ausführliche Beschreibung der Aktivität';

CREATE TABLE a23_activity_activity (
    activity_activity_id    integer NOT NULL,
    owner_id                integer NOT NULL,
    aim_id                  integer NOT NULL
);

COMMENT ON TABLE a23_activity_activity
IS 'Verknüpft Aktivitäten mit Aktivitäten';
COMMENT ON COLUMN a23_activity_activity.owner_id
IS 'ID der Aktivität die Eigentümer des Links ist';
COMMENT ON COLUMN a23_activity_activity.aim_id
IS 'ID der Aktivität die Ziel des Links ist';

CREATE TABLE a23_activity_container (
    activity_container_id   integer NOT NULL,
    activity_id             integer NOT NULL,
    container_id            integer NOT NULL
);

COMMENT ON TABLE a23_activity_container
IS 'Verknüpft Container mit Aktivitäten';
COMMENT ON COLUMN a23_activity_container.activity_id
IS 'ID der Aktivität';
COMMENT ON COLUMN a23_activity_container.container_id
IS 'ID eines Containers';

CREATE TABLE a23_activity_filestore (
    activity_filestore_id   integer NOT NULL,
    activity_id             integer NOT NULL,
    filestore_id            integer NOT NULL
);

COMMENT ON TABLE a23_activity_filestore
IS 'Verknüpft Dateien mit Aktivitäten';
COMMENT ON COLUMN a23_activity_filestore.activity_id
IS 'ID der Aktivität';
COMMENT ON COLUMN a23_activity_filestore.filestore_id
IS 'ID einer Datei';

CREATE TABLE a23_activity_logbook (
    log_id      integer                     NOT NULL,
    activity_id integer                     NOT NULL,
    editor_id   integer                     NOT NULL,
    time_stamp  timestamp without time zone NOT NULL,
    title       text                        NOT NULL,
    note        text   DEFAULT ''::text     NOT NULL
);

COMMENT ON TABLE a23_activity_logbook
IS 'Protokollieren/Dokumentieren von Ereignissen';
COMMENT ON COLUMN a23_activity_logbook.log_id
IS 'ID des Protokolleintrags';
COMMENT ON COLUMN a23_activity_logbook.activity_id
IS 'ID der des Protokolls der Aktivität';
COMMENT ON COLUMN a23_activity_logbook.editor_id
IS 'Verweis auf eine ID eines Suchers, der der Autor ist.';
COMMENT ON COLUMN a23_activity_logbook.time_stamp
IS 'Erstellungsdatum';
COMMENT ON COLUMN a23_activity_logbook.title
IS 'Überschrift des Protokolleintrags';
COMMENT ON COLUMN a23_activity_logbook.note
IS 'Die eigentliche Meldung';

CREATE TABLE a23_activity_provider (
    link_id     integer NOT NULL,
    activity_id integer NOT NULL,
    provider_id integer NOT NULL
);


COMMENT ON TABLE a23_activity_provider
IS 'Verknüpft Anbieter mit Aktivitäten';
COMMENT ON COLUMN a23_activity_provider.activity_id
IS 'ID der Aktivität';
COMMENT ON COLUMN a23_activity_provider.provider_id
IS 'ID eines Anbieters';

CREATE TABLE a23_activity_seeker (
    link_id     integer NOT NULL,
    activity_id integer NOT NULL,
    seeker_id   integer NOT NULL
);

COMMENT ON TABLE a23_activity_seeker
IS 'Verknüpft Sucher mit Aktivitäten';
COMMENT ON COLUMN a23_activity_seeker.activity_id
IS 'ID der Aktivität';
COMMENT ON COLUMN a23_activity_seeker.seeker_id
IS 'ID des Suchers';

CREATE TABLE a23_common_container (
    common_container_id integer NOT NULL,
    name                text NOT NULL
);

COMMENT ON TABLE a23_common_container
IS 'Container-Bezeichner um verschiedene Dinge
        (z. B. Dateien) thematisch zusammenzufassen';
COMMENT ON COLUMN a23_common_container.common_container_id
IS 'ID des Containers';
COMMENT ON COLUMN a23_common_container.name
IS 'Bezeichner des Containers';

CREATE TABLE a23_file_reserve (
    a23_file_reserve_id integer                     NOT NULL,
    file_id             integer                     NOT NULL,
    editor_id           integer                     NOT NULL,
    start_date          timestamp without time zone NOT NULL,
    end_date            timestamp without time zone NOT NULL,
    note text                                       NOT NULL
);


COMMENT ON TABLE a23_file_reserve
IS 'Zur Vermeidung von Bearbeitungskonflikten,
        Reservierungen für die Tabelle filestore.';
COMMENT ON COLUMN a23_file_reserve.file_id
IS 'ID der Datei, die reserviert werden soll';
COMMENT ON COLUMN a23_file_reserve.editor_id
IS 'ID der Person, die eine Reservierung angefordert hat';
COMMENT ON COLUMN a23_file_reserve.start_date
IS 'Wann die Reservierung gesetzt wurde';
COMMENT ON COLUMN a23_file_reserve.end_date
IS 'Bis wann reserviert wurde';
COMMENT ON COLUMN a23_file_reserve.note
IS 'Erläuterungen und Kommentare zur Reservierung';

CREATE TABLE a23_filestore (
    file_id         integer                         NOT NULL,
    name            text        DEFAULT ''::text    NOT NULL,
    version_of_id   integer,
    bin_data        bytea                           NOT NULL,
    version_tag     text        DEFAULT ''::text    NOT NULL,
    md5_sum         text                            NOT NULL,
    create_date     timestamp   without time zone   NOT NULL,
    delete_date     timestamp   without time zone,
    file_summary    text        DEFAULT ''::text    NOT NULL
);

COMMENT ON TABLE a23_filestore
IS 'Tabelle zum Speichern von (Binär-)Dateien';
COMMENT ON COLUMN a23_filestore.file_id
IS 'ID einer Datei/eines Datensatzes)';
COMMENT ON COLUMN a23_filestore.name
IS 'Dateiename';
COMMENT ON COLUMN a23_filestore.version_of_id
IS 'Die ID der (alten) Datei die mit dieser eine
        neue Version hat.';
COMMENT ON COLUMN a23_filestore.bin_data
IS 'Die gespeicherten Binär-Daten';
COMMENT ON COLUMN a23_filestore.version_tag
IS 'Name der Version zur besseren Wiedererkennung
        (z. B. eine Nummer)';
COMMENT ON COLUMN a23_filestore.md5_sum
IS 'MD5-Summe (zur Duplikatsuche)';
COMMENT ON COLUMN a23_filestore.create_date
IS 'Erstellungsdatum';
COMMENT ON COLUMN a23_filestore.delete_date
IS 'Löschdatum (z. B. beim Ersetzen durch neue Version)';
COMMENT ON COLUMN a23_filestore.file_summary
IS 'Beschreibungstext zur gespeicherten Datei';

CREATE TABLE a23_filestore_container (
    filestore_container_id  integer NOT NULL,
    tag_id                  integer NOT NULL,
    file_id                 integer NOT NULL
);

COMMENT ON TABLE a23_filestore_container
IS 'Zuordnung von Dateien in Containern';
COMMENT ON COLUMN a23_filestore_container.tag_id
IS 'Verweis auf die ID eines existierenden Containers';
COMMENT ON COLUMN a23_filestore_container.file_id
IS 'Verweis auf die ID einer existierenden Datei';

CREATE TABLE a23_global_conf (
    conf_id     integer NOT NULL,
    name_space  text    NOT NULL,
    conf_type   text    NOT NULL,
    conf_value  text    NOT NULL
);

COMMENT ON TABLE a23_global_conf
IS 'Tabelle für globalen Konfigurationsparameter,
        die mehere User benutzen.';
COMMENT ON COLUMN a23_global_conf.conf_id
IS 'ID eines Wertes';
COMMENT ON COLUMN a23_global_conf.name_space
IS 'Zum Gruppieren von gespeicherten Werten';
COMMENT ON COLUMN a23_global_conf.conf_type
IS 'Bezeichner für einen Wert';
COMMENT ON COLUMN a23_global_conf.conf_value
IS 'Der eigentliche Wert';

CREATE TABLE a23_handicap (
    handicap_type   text    NOT NULL,
    handicap_id     integer NOT NULL
);

COMMENT ON TABLE a23_handicap
IS 'Einschränkungen und ihre IDs für Angebote und Sucher';
COMMENT ON COLUMN a23_handicap.handicap_type
IS 'Bezeichner einer Einschränkung';
COMMENT ON COLUMN a23_handicap.handicap_id
IS 'ID der Einschränkung';

CREATE TABLE a23_industry (
    industry_id         integer NOT NULL,
    provider_id         integer NOT NULL,
    industry_identifier text    NOT NULL
);

COMMENT ON TABLE a23_industry
IS 'Für Zuordnung eines Anbieters zu einer Branche';
COMMENT ON COLUMN a23_industry.provider_id
IS 'Verweis auf einen existierenden Anbieter';
COMMENT ON COLUMN a23_industry.industry_identifier
IS 'Firma kann beliebig vielen Branchen angehören.';

CREATE TABLE a23_newsletter_log (
    newsletter_id   integer                     NOT NULL,
    subject         text                        NOT NULL,
    newsletter_body text                        NOT NULL,
    sent_from       text                        NOT NULL,
    create_date     timestamp without time zone NOT NULL,
    editor_id       integer                     NOT NULL
);

COMMENT ON TABLE a23_newsletter_log
IS 'Verschickter Newsletter';
COMMENT ON COLUMN a23_newsletter_log.newsletter_id
IS 'ID des Newsletters';
COMMENT ON COLUMN a23_newsletter_log.subject
IS 'Betreff des Newsletters';
COMMENT ON COLUMN a23_newsletter_log.newsletter_body
IS 'Text des Newsletters';
COMMENT ON COLUMN a23_newsletter_log.sent_from
IS 'Absendeadresse';
COMMENT ON COLUMN a23_newsletter_log.create_date
IS 'Zeitstempel';
COMMENT ON COLUMN a23_newsletter_log.editor_id
IS 'ID des Sachbearbeiters, der den Newsletter versendet.';

CREATE TABLE a23_newsletter_sent_to_seeker (
    a23_newsletter_sent_to_seeker_id    integer NOT NULL,
    newsletter_id                       integer NOT NULL,
    mail_address                        text    NOT NULL,
    seeker_id                           integer NOT NULL
);

COMMENT ON TABLE a23_newsletter_sent_to_seeker
IS 'Verknüpft Newsletter mit dem Sachbearbeiter, der er ihn erhalten hat.';
COMMENT ON COLUMN a23_newsletter_sent_to_seeker.newsletter_id
IS 'ID des Newsletters';
COMMENT ON COLUMN a23_newsletter_sent_to_seeker.mail_address
IS 'Die E-Mail-Adresse, an die verschickt wurde.';
COMMENT ON COLUMN a23_newsletter_sent_to_seeker.seeker_id
IS 'Der Sucher, der eine Newsletter erhalten hat.';

CREATE TABLE a23_offer (
    offer_id        integer                                 NOT NULL,
    offers_date     date        DEFAULT '2008-11-16'::date  NOT NULL,
    info_source     text        DEFAULT ''::text            NOT NULL,
    provider_id     integer                                 NOT NULL,
    job_count       integer     DEFAULT 1                   NOT NULL,
    salutation      text        DEFAULT ''::text            NOT NULL,
    note            text        DEFAULT ''::text            NOT NULL
);

COMMENT ON TABLE a23_offer
IS 'Tabelle für Angebote/Annoncen';
COMMENT ON COLUMN a23_offer.offer_id
IS 'Eindeutige, fortlaufende ID-Nummer';
COMMENT ON COLUMN a23_offer.offers_date
IS 'Von wann das Angebot ist';
COMMENT ON COLUMN a23_offer.info_source
IS 'Wo das Angebot her ist (z. B. Zeitungsname)';
COMMENT ON COLUMN a23_offer.provider_id
IS 'Verweis auf einen existierenden Anbieter';
COMMENT ON COLUMN a23_offer.job_count
IS 'Wieviel von etwas Angeboten wird';
COMMENT ON COLUMN a23_offer.salutation
IS 'Anrede in Form von /Herr/, /Frau/ usw.';
COMMENT ON COLUMN a23_offer.note
IS 'Notizen und Ergänzungen';

CREATE TABLE a23_offer_link_to_handicap (
    offer_handicap_id   integer NOT NULL,
    offer_id            integer NOT NULL,
    handicap_id         integer NOT NULL
);

COMMENT ON TABLE a23_offer_link_to_handicap
IS 'Zuordnung der Einschränkungen zu Angeboten (z. B. keine Schichtarbeit)';
COMMENT ON COLUMN a23_offer_link_to_handicap.offer_id
IS 'ID eines Angebots';
COMMENT ON COLUMN a23_offer_link_to_handicap.handicap_id
IS 'ID einer Einschränkung';

CREATE TABLE a23_offer_link_to_quality (
    offer_quality_id    integer NOT NULL,
    offer_id            integer NOT NULL,
    quality_id          integer NOT NULL
);

COMMENT ON TABLE a23_offer_link_to_quality
IS 'Zuordnung von Angeboten zu positiven Merkmalen ("Qualitäten") ';
COMMENT ON COLUMN a23_offer_link_to_quality.offer_id
IS 'ID einer Stelle';
COMMENT ON COLUMN a23_offer_link_to_quality.quality_id
IS 'ID einer Qualität';

CREATE TABLE a23_offer_link_to_stuff (
    offer_stuff_id  integer NOT NULL,
    stuff_id        integer NOT NULL,
    offer_id        integer NOT NULL
);

COMMENT ON TABLE a23_offer_link_to_stuff
IS 'Verknüpfung von Angeboten mit Eigenschaften';
COMMENT ON COLUMN a23_offer_link_to_stuff.stuff_id
IS 'ID einer Eigenschaft';
COMMENT ON COLUMN a23_offer_link_to_stuff.offer_id
IS 'ID eines Angebots';

CREATE TABLE a23_provider (
    provider_id     integer                         NOT NULL,
    district        text        DEFAULT ''::text    NOT NULL,
    name            text,
    street          text        DEFAULT ''::text    NOT NULL,
    housenumber     text        DEFAULT ''::text    NOT NULL,
    zip_code        integer     DEFAULT 0           NOT NULL,
    city            text        DEFAULT ''::text    NOT NULL,
    member_count    integer     DEFAULT 1           NOT NULL,
    parent_company  integer,
    note           text        DEFAULT ''::text   NOT NULL
);


COMMENT ON TABLE a23_provider
IS 'Tabelle für Stammdaten der Anbieter.';
COMMENT ON COLUMN a23_provider.provider_id
IS 'Eindeutige ID, die sich nicht mehe ändern sollte.';
COMMENT ON COLUMN a23_provider.district
IS 'Frei wählbar, um Anbieter geografisch einzuordnen.';
COMMENT ON COLUMN a23_provider.name
IS 'Name des Anbiters (keine Differenzierung Vor- und Zuname).';
COMMENT ON COLUMN a23_provider.street
IS 'Straße der Adresse des Anbieters';
COMMENT ON COLUMN a23_provider.housenumber
IS 'Hausnummer der Adresse des Anbieters.';
COMMENT ON COLUMN a23_provider.zip_code
IS 'Postleitzahl der Adresse des Anbieters';
COMMENT ON COLUMN a23_provider.city
IS 'Ort der Adresse des Anbieters.';
COMMENT ON COLUMN a23_provider.member_count
IS 'Mitarbeiteranzahl eines Anbiters';
COMMENT ON COLUMN a23_provider.parent_company
IS 'Verweis auf einen anderen Anbieter, wenn
        dieser dem einen untersteht oder dazugehört.';
COMMENT ON COLUMN a23_provider.note
IS 'Notizen und Vermerke.';

CREATE TABLE a23_provider_black_list (
    provider_black_list_id  integer NOT NULL,
    provider_id             integer NOT NULL
);

COMMENT ON TABLE a23_provider_black_list
IS 'Anbieter die gesperrt sind und nicht berücksichtigt
        werden sollen.';
COMMENT ON COLUMN a23_provider_black_list.provider_id
IS 'ID eines gesperrten Anbieters';

CREATE TABLE a23_provider_domain (
    provider_id     integer     NOT NULL,
    domain_name     text        NOT NULL
);


COMMENT ON TABLE a23_provider_domain
IS 'Zuordnungen einer Internet-Domain zu einem Anbieter';
COMMENT ON COLUMN a23_provider_domain.provider_id
IS 'Verweis auf einen existierenden Anbieter';
COMMENT ON COLUMN a23_provider_domain.domain_name
IS 'Internet-Domain die nur einmal vorkommen darf.';

CREATE TABLE a23_provider_member (
    provider_id         integer                 NOT NULL,
    member_id           integer                 NOT NULL,
    name                text                    NOT NULL,
    department          text DEFAULT ''::text   NOT NULL,
    task                text DEFAULT ''::text   NOT NULL,
    consultation_hours  text DEFAULT ''::text   NOT NULL,
    absence             text DEFAULT ''::text   NOT NULL,
    note                text DEFAULT ''::text   NOT NULL
);

COMMENT ON TABLE a23_provider_member
IS 'Informationen zu Ansprechpartnern von Anbietern';
COMMENT ON COLUMN a23_provider_member.provider_id
IS 'Anbieter zu der die Kontaktperson gehört';
COMMENT ON COLUMN a23_provider_member.member_id
IS 'Eindeutige, fortlaufende ID für die Kontaktperson';
COMMENT ON COLUMN a23_provider_member.name
IS 'Feld für Zu-und Vorname';
COMMENT ON COLUMN a23_provider_member.department
IS 'Falls vorhanden Abteilung/Filiale';
COMMENT ON COLUMN a23_provider_member.task
IS 'Aufgabe oder Position der Kontaktperson';
COMMENT ON COLUMN a23_provider_member.consultation_hours
IS 'Vermerk über Anwesenheit';
COMMENT ON COLUMN a23_provider_member.absence
IS 'Vermerk über Abwesenheitszeiten';
COMMENT ON COLUMN a23_provider_member.note
IS 'Anmerkungen und Notizen';

CREATE TABLE a23_provider_member_email (
    email_id            integer                 NOT NULL,
    provider_id         integer,
    member_id           integer,
    email_local_part    text DEFAULT ''::text   NOT NULL,
    email_domain        text DEFAULT ''::text   NOT NULL
);

COMMENT ON TABLE a23_provider_member_email
IS 'Zuordnung von E-Mail-Adressen zu Ansprechpartnern';
COMMENT ON COLUMN a23_provider_member_email.provider_id
IS 'ID eines eines Anbieters';
COMMENT ON COLUMN a23_provider_member_email.member_id
IS 'ID eines Ansprechpartnes eines Anbieters';
COMMENT ON COLUMN a23_provider_member_email.email_local_part
IS 'Der Teil der E-Mail-Adresse, der vor "@" steht
        ("peter" von peter@muster-firma.com).';
COMMENT ON COLUMN a23_provider_member_email.email_domain
IS 'Der Teil der E-Mail-Adresse, der nach "@" steht
        ("muster-firma.com" von peter@muster-firma.com).';

CREATE TABLE a23_provider_member_phone (
    phone_id        integer                 NOT NULL,
    member_id        integer                 NOT NULL,
    phone_no        text DEFAULT ''::text   NOT NULL,
    fax_or_phone    text DEFAULT ''::text   NOT NULL
);

COMMENT ON TABLE a23_provider_member_phone
IS 'Zuordnung von Tel.-Nummern zu Anbieter-Ansprechpartnern';
COMMENT ON COLUMN a23_provider_member_phone.member_id
IS 'ID eines Ansprechpartnes eines Anbieters (Tabellenbezeichner ist noch irreführend!)';
COMMENT ON COLUMN a23_provider_member_phone.phone_no
IS 'Die Nummer des Mitarbeiters';
COMMENT ON COLUMN a23_provider_member_phone.fax_or_phone
IS 'Der Bezeichner: Tel, Fax, ICQ, usw.';

CREATE TABLE a23_provider_phone (
    provider_id     integer NOT NULL,
    phone_no        text    NOT NULL,
    fax_or_phone    text    NOT NULL
);

COMMENT ON TABLE a23_provider_phone
IS 'Zuordnung einer Tel.- oder Fax-Nummer zu einem Anbieter';
COMMENT ON COLUMN a23_provider_phone.provider_id
IS 'Verweis auf einen existierenden Anbieter';
COMMENT ON COLUMN a23_provider_phone.phone_no
IS 'Eine Nummer kann immer nur einem Anbieter gehören,
        aber ein Anbieter kann mehrere Nummern haben.';
COMMENT ON COLUMN a23_provider_phone.fax_or_phone
IS 'Ob es sich um eine Tel.- oder Fax-Nummer oder
        etwas anderes handelt.';

CREATE TABLE a23_provider_pobox (
    provider_id     integer NOT NULL,
    pobox_no        text    NOT NULL
);

COMMENT ON TABLE a23_provider_pobox
IS 'Zuordnung der Postfachnummern des Anbieters';
COMMENT ON COLUMN a23_provider_pobox.provider_id
IS 'Verweis auf einen existierenden Anbieter';
COMMENT ON COLUMN a23_provider_pobox.pobox_no
IS 'Postfachanschrift - darf nur einer Firma gehören.';

CREATE TABLE a23_quality (
    quality_type    text    NOT NULL,
    quality_id      integer NOT NULL
);

COMMENT ON TABLE a23_quality
IS 'Qualitäten und ihre IDs (z. B. für Führerschein-Klassen)';
COMMENT ON COLUMN a23_quality.quality_type
IS 'Bezeichner der Qualität';
COMMENT ON COLUMN a23_quality.quality_id
IS 'ID der Qualität';

CREATE TABLE a23_request (
    seeker_id       integer,
    editor_id       integer,
    request_id      integer                             NOT NULL,
    request_date    date DEFAULT DATE'now'              NOT NULL,
    situation       text DEFAULT 'no defined'::text     NOT NULL,
    note            text DEFAULT ''::text               NOT NULL,
    offer_id        integer                             NOT NULL
);

COMMENT ON TABLE a23_request
IS 'Tabelle für Kontaktaufnahmen, die an Anbieter rausgegingen.';
COMMENT ON COLUMN a23_request.seeker_id
IS 'Sucher der den Kontakt hergestellt hat oder für
        den er hergestellt wurde.';
COMMENT ON COLUMN a23_request.editor_id
IS 'Derjenige, der die Kontaktaufnahme bearbeitet/erstellt hat.';
COMMENT ON COLUMN a23_request.request_id
IS 'Fortlaufende, eindeutige Nummer';
COMMENT ON COLUMN a23_request.request_date
IS 'Erstellungsdatum';
COMMENT ON COLUMN a23_request.situation
IS 'In welchen Stadium sich der Kontakt befindet';
COMMENT ON COLUMN a23_request.note
IS 'Kommentare und Anmerkungen';
COMMENT ON COLUMN a23_request.offer_id
IS 'Das Angebot, auf das sich der Kontakt bezieht.';

CREATE TABLE a23_seeker (
    seeker_no           text,
    seeker_id           integer                             NOT NULL,
    name                text                                NOT NULL,
    street              text    DEFAULT ''::text            NOT NULL,
    housenumber         text    DEFAULT ''::text            NOT NULL,
    zip_code            integer DEFAULT 0                   NOT NULL,
    city                text    DEFAULT ''::text            NOT NULL,
    birthday            date    DEFAULT DATE'1753-01-01'    NOT NULL,
    salutation          text    DEFAULT ''::text            NOT NULL,
    joining             date    DEFAULT DATE'now'           NOT NULL,
    priority            integer DEFAULT 50                  NOT NULL,
    note                text    DEFAULT ''::text            NOT NULL,
    address_addition    text    DEFAULT ''::text            NOT NULL
);

COMMENT ON TABLE a23_seeker
IS 'In dieser Tabelle werden die Stammdaten des Suchers gespeichert.';
COMMENT ON COLUMN a23_seeker.seeker_no
IS 'Ist eine interne, frei wählbare Verwaltungsnummer.
        Könnte sich mal ändern (z. B. wegen Umzug oder
        Abteilungswechsel).';
COMMENT ON COLUMN a23_seeker.seeker_id
IS 'Eindeutige ID-Nummer, die statisch verwendet werden soll';
COMMENT ON COLUMN a23_seeker.name
IS 'Name des Suchers. Nach- und Vorname sollte Komma-getrennt
        sein. Nachname zuerst';
COMMENT ON COLUMN a23_seeker.street
IS 'Straße der Postanschrift';
COMMENT ON COLUMN a23_seeker.housenumber
IS 'Hausnummer der Postanschrift';
COMMENT ON COLUMN a23_seeker.zip_code
IS 'Postleitzahl der Postanschrift';
COMMENT ON COLUMN a23_seeker.city
IS 'Ort der Postanschrift';
COMMENT ON COLUMN a23_seeker.birthday
IS 'Geburtsdatum des Suchers';
COMMENT ON COLUMN a23_seeker.salutation
IS 'Anrede des Suchers: Herr, Frau, Firma, Familie usw.';
COMMENT ON COLUMN a23_seeker.joining
IS 'Meint Erfassungsdatum am...';
COMMENT ON COLUMN a23_seeker.priority
IS 'Ob der Sucher bei der Suche bevorzugt werden soll,
        um z. B. mehr beworben zu werden.';
COMMENT ON COLUMN a23_seeker.note
IS 'Sonstige Anmerkungen....';
COMMENT ON COLUMN a23_seeker.address_addition
IS 'Adresszusätze wie etwa Land';

CREATE TABLE a23_seeker_link_to_handicap (
    seeker_handicap_id      integer NOT NULL,
    seeker_id               integer NOT NULL,
    handicap_id             integer NOT NULL
);

COMMENT ON TABLE a23_seeker_link_to_handicap
IS 'Zuordnung der Einschränkungen zu Suchern (z. B. keine Schichtarbeit)';
COMMENT ON COLUMN a23_seeker_link_to_handicap.seeker_id
IS 'ID eines Suchers';
COMMENT ON COLUMN a23_seeker_link_to_handicap.handicap_id
IS 'ID einer Einschränkung';

CREATE TABLE a23_seeker_link_to_quality (
    seeker_quality_id   integer NOT NULL,
    seeker_id           integer NOT NULL,
    quality_id          integer NOT NULL
);

COMMENT ON TABLE a23_seeker_link_to_quality
IS 'Zuordnung von Suchern zu positiven Merkmalen ("Qualitäten")';
COMMENT ON COLUMN a23_seeker_link_to_quality.seeker_id
IS 'ID eines Suchers';
COMMENT ON COLUMN a23_seeker_link_to_quality.quality_id
IS 'ID einer Qualität';

CREATE TABLE a23_seeker_link_to_stuff (
    seeker_stuff_id     integer     NOT NULL,
    stuff_id            integer     NOT NULL,
    seeker_id           integer     NOT NULL
);

COMMENT ON TABLE a23_seeker_link_to_stuff
IS 'Verknüpfung von Eigenschaften mit Suchern';
COMMENT ON COLUMN a23_seeker_link_to_stuff.stuff_id
IS 'ID einer Eigenschaft z.B. Beruf';
COMMENT ON COLUMN a23_seeker_link_to_stuff.seeker_id
IS 'ID eines Suchers';

CREATE TABLE a23_seeker_logbook (
    log_id      integer                         NOT NULL,
    seeker_id   integer                         NOT NULL,
    editor_id   integer                         NOT NULL,
    time_stamp  timestamp without time zone     NOT NULL,
    title       text                            NOT NULL,
    note        text    DEFAULT ''::text        NOT NULL
);

COMMENT ON TABLE a23_seeker_logbook
IS 'Protokollieren/Dokumentieren von Sucher-Ereignissen';
COMMENT ON COLUMN a23_seeker_logbook.log_id
IS 'ID des Protokoll-Eintrags';
COMMENT ON COLUMN a23_seeker_logbook.seeker_id
IS 'ID/Sucher zum Protokoll';
COMMENT ON COLUMN a23_seeker_logbook.editor_id
IS 'Verweis auf die ID/Sucher des Autors';
COMMENT ON COLUMN a23_seeker_logbook.time_stamp
IS 'Erstellungsdatum';
COMMENT ON COLUMN a23_seeker_logbook.title
IS 'Überschrift des Protokoll-Eintrags';
COMMENT ON COLUMN a23_seeker_logbook.note
IS 'Die eigentliche Meldung';

CREATE TABLE a23_seeker_phone (
    phone_id    integer                         NOT NULL,
    seeker_id   integer,
    phone_no    text        DEFAULT ''::text    NOT NULL
);

COMMENT ON TABLE a23_seeker_phone
IS 'Telefonnummern der Sucher';
COMMENT ON COLUMN a23_seeker_phone.seeker_id
IS 'ID eines Suchers';
COMMENT ON COLUMN a23_seeker_phone.phone_no
IS 'Nummer des Suchers';

CREATE TABLE a23_stuff_type (
    stuff_id    integer NOT NULL,
    stuff_type  text
);

COMMENT ON TABLE a23_stuff_type
IS 'Eigenschaftsbezeichnungen  z.B. Berufbezeichnung mit eindeutigen IDs';
COMMENT ON COLUMN a23_stuff_type.stuff_id
IS 'ID einer Eigenschaft';
COMMENT ON COLUMN a23_stuff_type.stuff_type
IS 'Der Bezeichner der Eigenschaft z.B. Beruf';

CREATE TABLE a23_version (
    a23_version_id  integer NOT NULL,
    major_release   integer NOT NULL,
    minor_release   integer NOT NULL,
    patch_level     integer NOT NULL
);

COMMENT ON TABLE a23_version
IS 'Tabelle speichert die Programmversion für die die Tabelle erstellt wurde.';

-- ################# SEQUENCE #########################################

CREATE SEQUENCE a23_file_reserve_a23_file_reserve_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE a23_file_reserve_a23_file_reserve_id_seq OWNED BY a23_file_reserve.a23_file_reserve_id;
COMMENT ON SEQUENCE a23_file_reserve_a23_file_reserve_id_seq
IS 'Gehört zu a23_file_reserve.a23_file_reserve_id';
SELECT pg_catalog.setval('a23_file_reserve_a23_file_reserve_id_seq', 1, false);

CREATE SEQUENCE a23_newsletter_log_newsletter_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE a23_newsletter_log_newsletter_id_seq OWNED BY a23_newsletter_log.newsletter_id;
COMMENT ON SEQUENCE a23_newsletter_log_newsletter_id_seq
IS 'Gehört zu a23_newsletter_log.newsletter_id';
SELECT pg_catalog.setval('a23_newsletter_log_newsletter_id_seq', 1, false);

CREATE SEQUENCE a23_newsletter_sent_to_seeker_a23_newsletter_sent_to_seeker_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;



ALTER SEQUENCE a23_newsletter_sent_to_seeker_a23_newsletter_sent_to_seeker_seq OWNED BY a23_newsletter_sent_to_seeker.a23_newsletter_sent_to_seeker_id;
COMMENT ON SEQUENCE a23_newsletter_sent_to_seeker_a23_newsletter_sent_to_seeker_seq
IS 'Gehört zu a23_newsletter_sent_to_seeker.a23_newsletter_sent_to_seeker_id';
SELECT pg_catalog.setval('a23_newsletter_sent_to_seeker_a23_newsletter_sent_to_seeker_seq', 1, false);

CREATE SEQUENCE a23_seeker_logbook_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER SEQUENCE a23_seeker_logbook_id_seq OWNED BY a23_seeker_logbook.log_id;

SELECT pg_catalog.setval('a23_seeker_logbook_id_seq', 1, false);

CREATE SEQUENCE a23_version_a23_version_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE a23_version_a23_version_id_seq OWNED BY a23_version.a23_version_id;

SELECT pg_catalog.setval('a23_version_a23_version_id_seq', 15, true);

CREATE SEQUENCE activity_activity_activity_activity_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE activity_activity_activity_activity_id_seq OWNED BY a23_activity_activity.activity_activity_id;

SELECT pg_catalog.setval('activity_activity_activity_activity_id_seq', 1, false);

CREATE SEQUENCE activity_container_activity_container_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE activity_container_activity_container_id_seq OWNED BY a23_activity_container.activity_container_id;

SELECT pg_catalog.setval('activity_container_activity_container_id_seq', 1, false);

CREATE SEQUENCE activity_filestore_activity_filestore_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE activity_filestore_activity_filestore_id_seq OWNED BY a23_activity_filestore.activity_filestore_id;

SELECT pg_catalog.setval('activity_filestore_activity_filestore_id_seq', 1, false);

CREATE SEQUENCE activity_firma_activity_firma_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE activity_firma_activity_firma_id_seq OWNED BY a23_activity_provider.link_id;

SELECT pg_catalog.setval('activity_firma_activity_firma_id_seq', 1, false);

CREATE SEQUENCE activity_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE activity_id_seq OWNED BY a23_activity.activity_id;

SELECT pg_catalog.setval('activity_id_seq', 1, false);

CREATE SEQUENCE activity_logbook_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE activity_logbook_id_seq OWNED BY a23_activity_logbook.log_id;
SELECT pg_catalog.setval('activity_logbook_id_seq', 1, false);

CREATE SEQUENCE activity_mitglied_activity_mitglied_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE activity_mitglied_activity_mitglied_id_seq OWNED BY a23_activity_seeker.link_id;
SELECT pg_catalog.setval('activity_mitglied_activity_mitglied_id_seq', 1, false);

CREATE SEQUENCE beruf_berufs_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE beruf_berufs_id_seq OWNED BY a23_stuff_type.stuff_id;
SELECT pg_catalog.setval('beruf_berufs_id_seq', 1, false);

CREATE SEQUENCE bewerbung_bewerbungs_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE bewerbung_bewerbungs_id_seq OWNED BY a23_request.request_id;
SELECT pg_catalog.setval('bewerbung_bewerbungs_id_seq', 1, false);

CREATE SEQUENCE branchen_kat_branchen_kat_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE branchen_kat_branchen_kat_id_seq OWNED BY a23_industry.industry_id;
SELECT pg_catalog.setval('branchen_kat_branchen_kat_id_seq', 1, false);

CREATE SEQUENCE common_container_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE common_container_id_seq OWNED BY a23_common_container.common_container_id;
SELECT pg_catalog.setval('common_container_id_seq', 1, false);

CREATE SEQUENCE einschraenkung_merkmal_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE einschraenkung_merkmal_id_seq OWNED BY a23_handicap.handicap_id;
SELECT pg_catalog.setval('einschraenkung_merkmal_id_seq', 1, false);

CREATE SEQUENCE einschraenkung_mitglied_einschraenkung_mitglied_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE einschraenkung_mitglied_einschraenkung_mitglied_id_seq OWNED BY a23_seeker_link_to_handicap.seeker_handicap_id;
SELECT pg_catalog.setval('einschraenkung_mitglied_einschraenkung_mitglied_id_seq', 1, false);

CREATE SEQUENCE einschraenkung_stellen_einschraenkung_stellen_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE einschraenkung_stellen_einschraenkung_stellen_id_seq OWNED BY a23_offer_link_to_handicap.offer_handicap_id;
SELECT pg_catalog.setval('einschraenkung_stellen_einschraenkung_stellen_id_seq', 1, false);

CREATE SEQUENCE email_email_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE email_email_id_seq OWNED BY a23_provider_member_email.email_id;
SELECT pg_catalog.setval('email_email_id_seq', 1, false);

CREATE SEQUENCE filestore_container_filestore_container_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE filestore_container_filestore_container_id_seq OWNED BY a23_filestore_container.filestore_container_id;
SELECT pg_catalog.setval('filestore_container_filestore_container_id_seq', 1, false);

CREATE SEQUENCE filestore_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE filestore_id_seq OWNED BY a23_filestore.file_id;
SELECT pg_catalog.setval('filestore_id_seq', 1, false);

CREATE SEQUENCE firma_firmen_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE firma_firmen_id_seq OWNED BY a23_provider.provider_id;
SELECT pg_catalog.setval('firma_firmen_id_seq', 1, false);

CREATE SEQUENCE firmen_black_list_firmen_black_list_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE firmen_black_list_firmen_black_list_id_seq OWNED BY a23_provider_black_list.provider_black_list_id;
SELECT pg_catalog.setval('firmen_black_list_firmen_black_list_id_seq', 1, false);

CREATE SEQUENCE firmen_mitarbeiter_mitarbeiter_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE firmen_mitarbeiter_mitarbeiter_id_seq OWNED BY a23_provider_member.member_id;
SELECT pg_catalog.setval('firmen_mitarbeiter_mitarbeiter_id_seq', 1, false);

CREATE SEQUENCE firmen_mitarbeiter_tel_nr_firmen_mitarbeiter_tel_nr_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE firmen_mitarbeiter_tel_nr_firmen_mitarbeiter_tel_nr_id_seq OWNED BY a23_provider_member_phone.phone_id;
SELECT pg_catalog.setval('firmen_mitarbeiter_tel_nr_firmen_mitarbeiter_tel_nr_id_seq', 1, false);

CREATE SEQUENCE global_conf_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE global_conf_id_seq OWNED BY a23_global_conf.conf_id;
SELECT pg_catalog.setval('global_conf_id_seq', 1, false);

CREATE SEQUENCE mitglied_mitglieds_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE mitglied_mitglieds_id_seq OWNED BY a23_seeker.seeker_id;
SELECT pg_catalog.setval('mitglied_mitglieds_id_seq', 1, false);

CREATE SEQUENCE mitgliederberufe_mitgliederberufe_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE mitgliederberufe_mitgliederberufe_id_seq OWNED BY a23_seeker_link_to_stuff.seeker_stuff_id;
SELECT pg_catalog.setval('mitgliederberufe_mitgliederberufe_id_seq', 1, false);

CREATE SEQUENCE mitglieds_tel_nr_mitglieds_tel_nr_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE mitglieds_tel_nr_mitglieds_tel_nr_id_seq OWNED BY a23_seeker_phone.phone_id;
SELECT pg_catalog.setval('mitglieds_tel_nr_mitglieds_tel_nr_id_seq', 1, false);

CREATE SEQUENCE qualitaeten_merkmal_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE qualitaeten_merkmal_id_seq OWNED BY a23_quality.quality_id;
SELECT pg_catalog.setval('qualitaeten_merkmal_id_seq', 1, false);

CREATE SEQUENCE qualitaeten_mitglied_qualitaeten_mitglied_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE qualitaeten_mitglied_qualitaeten_mitglied_id_seq OWNED BY a23_seeker_link_to_quality.seeker_quality_id;
SELECT pg_catalog.setval('qualitaeten_mitglied_qualitaeten_mitglied_id_seq', 1, false);

CREATE SEQUENCE qualitaeten_stelle_qualitaeten_stelle_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE qualitaeten_stelle_qualitaeten_stelle_id_seq OWNED BY a23_offer_link_to_quality.offer_quality_id;
SELECT pg_catalog.setval('qualitaeten_stelle_qualitaeten_stelle_id_seq', 1, false);


CREATE SEQUENCE stelle_stellen_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE stelle_stellen_id_seq OWNED BY a23_offer.offer_id;
SELECT pg_catalog.setval('stelle_stellen_id_seq', 1, false);

CREATE SEQUENCE stellen_berufe_stellen_berufe_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE stellen_berufe_stellen_berufe_id_seq OWNED BY a23_offer_link_to_stuff.offer_stuff_id;
SELECT pg_catalog.setval('stellen_berufe_stellen_berufe_id_seq', 1, false);

-- ############### DEFAULT ###############################

ALTER TABLE a23_activity                  ALTER COLUMN activity_id                      SET DEFAULT nextval('activity_id_seq'::regclass);
ALTER TABLE a23_activity_activity         ALTER COLUMN activity_activity_id             SET DEFAULT nextval('activity_activity_activity_activity_id_seq'::regclass);
ALTER TABLE a23_activity_container        ALTER COLUMN activity_container_id            SET DEFAULT nextval('activity_container_activity_container_id_seq'::regclass);
ALTER TABLE a23_activity_filestore        ALTER COLUMN activity_filestore_id            SET DEFAULT nextval('activity_filestore_activity_filestore_id_seq'::regclass);
ALTER TABLE a23_activity_logbook          ALTER COLUMN log_id                           SET DEFAULT nextval('activity_logbook_id_seq'::regclass);
ALTER TABLE a23_activity_provider         ALTER COLUMN link_id                          SET DEFAULT nextval('activity_firma_activity_firma_id_seq'::regclass);
ALTER TABLE a23_activity_seeker           ALTER COLUMN link_id                          SET DEFAULT nextval('activity_mitglied_activity_mitglied_id_seq'::regclass);
ALTER TABLE a23_common_container          ALTER COLUMN common_container_id              SET DEFAULT nextval('common_container_id_seq'::regclass);
ALTER TABLE a23_file_reserve              ALTER COLUMN a23_file_reserve_id              SET DEFAULT nextval('a23_file_reserve_a23_file_reserve_id_seq'::regclass);
ALTER TABLE a23_filestore                 ALTER COLUMN file_id                          SET DEFAULT nextval('filestore_id_seq'::regclass);
ALTER TABLE a23_filestore_container       ALTER COLUMN filestore_container_id           SET DEFAULT nextval('filestore_container_filestore_container_id_seq'::regclass);
ALTER TABLE a23_global_conf               ALTER COLUMN conf_id                          SET DEFAULT nextval('global_conf_id_seq'::regclass);
ALTER TABLE a23_handicap                  ALTER COLUMN handicap_id                      SET DEFAULT nextval('einschraenkung_merkmal_id_seq'::regclass);
ALTER TABLE a23_industry                  ALTER COLUMN industry_id                      SET DEFAULT nextval('branchen_kat_branchen_kat_id_seq'::regclass);
ALTER TABLE a23_newsletter_log            ALTER COLUMN newsletter_id                    SET DEFAULT nextval('a23_newsletter_log_newsletter_id_seq'::regclass);
ALTER TABLE a23_newsletter_sent_to_seeker ALTER COLUMN a23_newsletter_sent_to_seeker_id SET DEFAULT nextval('a23_newsletter_sent_to_seeker_a23_newsletter_sent_to_seeker_seq'::regclass);
ALTER TABLE a23_offer                     ALTER COLUMN offer_id                         SET DEFAULT nextval('stelle_stellen_id_seq'::regclass);
ALTER TABLE a23_offer_link_to_handicap    ALTER COLUMN offer_handicap_id                SET DEFAULT nextval('einschraenkung_stellen_einschraenkung_stellen_id_seq'::regclass);
ALTER TABLE a23_offer_link_to_quality     ALTER COLUMN offer_quality_id                 SET DEFAULT nextval('qualitaeten_stelle_qualitaeten_stelle_id_seq'::regclass);
ALTER TABLE a23_offer_link_to_stuff       ALTER COLUMN offer_stuff_id                   SET DEFAULT nextval('stellen_berufe_stellen_berufe_id_seq'::regclass);
ALTER TABLE a23_provider                  ALTER COLUMN provider_id                      SET DEFAULT nextval('firma_firmen_id_seq'::regclass);
ALTER TABLE a23_provider_black_list       ALTER COLUMN provider_black_list_id           SET DEFAULT nextval('firmen_black_list_firmen_black_list_id_seq'::regclass);
ALTER TABLE a23_provider_member           ALTER COLUMN member_id                        SET DEFAULT nextval('firmen_mitarbeiter_mitarbeiter_id_seq'::regclass);
ALTER TABLE a23_provider_member_email     ALTER COLUMN email_id                         SET DEFAULT nextval('email_email_id_seq'::regclass);
ALTER TABLE a23_provider_member_phone     ALTER COLUMN phone_id                         SET DEFAULT nextval('firmen_mitarbeiter_tel_nr_firmen_mitarbeiter_tel_nr_id_seq'::regclass);
ALTER TABLE a23_quality                   ALTER COLUMN quality_id                       SET DEFAULT nextval('qualitaeten_merkmal_id_seq'::regclass);
ALTER TABLE a23_request                   ALTER COLUMN request_id                       SET DEFAULT nextval('bewerbung_bewerbungs_id_seq'::regclass);
ALTER TABLE a23_seeker                    ALTER COLUMN seeker_id                        SET DEFAULT nextval('mitglied_mitglieds_id_seq'::regclass);
ALTER TABLE a23_seeker_link_to_handicap   ALTER COLUMN seeker_handicap_id               SET DEFAULT nextval('einschraenkung_mitglied_einschraenkung_mitglied_id_seq'::regclass);
ALTER TABLE a23_seeker_link_to_quality    ALTER COLUMN seeker_quality_id                SET DEFAULT nextval('qualitaeten_mitglied_qualitaeten_mitglied_id_seq'::regclass);
ALTER TABLE a23_seeker_link_to_stuff      ALTER COLUMN seeker_stuff_id                  SET DEFAULT nextval('mitgliederberufe_mitgliederberufe_id_seq'::regclass);
ALTER TABLE a23_seeker_logbook            ALTER COLUMN log_id                           SET DEFAULT nextval('a23_seeker_logbook_id_seq'::regclass);
ALTER TABLE a23_seeker_phone              ALTER COLUMN phone_id                         SET DEFAULT nextval('mitglieds_tel_nr_mitglieds_tel_nr_id_seq'::regclass);
ALTER TABLE a23_stuff_type                ALTER COLUMN stuff_id                         SET DEFAULT nextval('beruf_berufs_id_seq'::regclass);
ALTER TABLE a23_version                   ALTER COLUMN a23_version_id                   SET DEFAULT nextval('a23_version_a23_version_id_seq'::regclass);


-- ############ CONSTRAINT #########################

ALTER TABLE ONLY a23_file_reserve               ADD CONSTRAINT a23_file_reserve_file_id_key         UNIQUE (file_id);
ALTER TABLE ONLY a23_file_reserve               ADD CONSTRAINT a23_file_reserve_pkey                PRIMARY KEY (a23_file_reserve_id);
ALTER TABLE ONLY a23_newsletter_log             ADD CONSTRAINT a23_newsletter_log_pkey              PRIMARY KEY (newsletter_id);
ALTER TABLE ONLY a23_newsletter_sent_to_seeker  ADD CONSTRAINT a23_newsletter_sent_to_seeker_pkey   PRIMARY KEY (a23_newsletter_sent_to_seeker_id);
ALTER TABLE ONLY a23_seeker_logbook             ADD CONSTRAINT a23_seeker_logbook_pkey              PRIMARY KEY (log_id);
ALTER TABLE ONLY a23_version                    ADD CONSTRAINT a23_version_pkey                     PRIMARY KEY (a23_version_id);
ALTER TABLE ONLY a23_activity_activity          ADD CONSTRAINT activity_activity_pkey               PRIMARY KEY (activity_activity_id);
ALTER TABLE ONLY a23_activity_container         ADD CONSTRAINT activity_container_pkey              PRIMARY KEY (activity_container_id);
ALTER TABLE ONLY a23_activity_filestore         ADD CONSTRAINT activity_filestore_pkey              PRIMARY KEY (activity_filestore_id);
ALTER TABLE ONLY a23_activity_provider          ADD CONSTRAINT activity_firma_pkey                  PRIMARY KEY (link_id);
ALTER TABLE ONLY a23_activity_logbook           ADD CONSTRAINT activity_logbook_pkey                PRIMARY KEY (log_id);
ALTER TABLE ONLY a23_activity_seeker            ADD CONSTRAINT activity_mitglied_pkey               PRIMARY KEY (link_id);
ALTER TABLE ONLY a23_activity                   ADD CONSTRAINT activity_pkey                        PRIMARY KEY (activity_id);
ALTER TABLE ONLY a23_stuff_type                 ADD CONSTRAINT beruf_berufsbezeichnung_key          UNIQUE (stuff_type);
ALTER TABLE ONLY a23_stuff_type                 ADD CONSTRAINT beruf_pkey                           PRIMARY KEY (stuff_id);
ALTER TABLE ONLY a23_request                    ADD CONSTRAINT bewerbung_pkey                       PRIMARY KEY (request_id);
ALTER TABLE ONLY a23_industry                   ADD CONSTRAINT branchen_kat_pkey                    PRIMARY KEY (industry_id);
ALTER TABLE ONLY a23_common_container           ADD CONSTRAINT common_container_name_key            UNIQUE (name);
ALTER TABLE ONLY a23_common_container           ADD CONSTRAINT common_container_pkey                PRIMARY KEY (common_container_id);
ALTER TABLE ONLY a23_provider_domain            ADD CONSTRAINT domain_name_pkey                     PRIMARY KEY (domain_name);
ALTER TABLE ONLY a23_handicap                   ADD CONSTRAINT einschraenkung_merkmal_key           UNIQUE (handicap_type);
ALTER TABLE ONLY a23_seeker_link_to_handicap    ADD CONSTRAINT einschraenkung_mitglied_pkey         PRIMARY KEY (seeker_handicap_id);
ALTER TABLE ONLY a23_handicap                   ADD CONSTRAINT einschraenkung_pkey                  PRIMARY KEY (handicap_id);
ALTER TABLE ONLY a23_offer_link_to_handicap     ADD CONSTRAINT einschraenkung_stellen_pkey          PRIMARY KEY (offer_handicap_id);
ALTER TABLE ONLY a23_provider_member_email      ADD CONSTRAINT email_pkey                           PRIMARY KEY (email_id);
ALTER TABLE ONLY a23_filestore_container        ADD CONSTRAINT filestore_container_pkey             PRIMARY KEY (filestore_container_id);
ALTER TABLE ONLY a23_filestore                  ADD CONSTRAINT filestore_pkey                       PRIMARY KEY (file_id);
ALTER TABLE ONLY a23_provider                   ADD CONSTRAINT firma_pkey                           PRIMARY KEY (provider_id);
ALTER TABLE ONLY a23_provider_black_list        ADD CONSTRAINT firmen_black_list_firmen_id_key      UNIQUE (provider_id);
ALTER TABLE ONLY a23_provider_black_list        ADD CONSTRAINT firmen_black_list_pkey               PRIMARY KEY (provider_black_list_id);
ALTER TABLE ONLY a23_provider_member            ADD CONSTRAINT firmen_mitarbeiter_pkey              PRIMARY KEY (member_id);
ALTER TABLE ONLY a23_provider_member_phone      ADD CONSTRAINT firmen_mitarbeiter_tel_nr_pkey       PRIMARY KEY (phone_id);
ALTER TABLE ONLY a23_provider_phone             ADD CONSTRAINT firmen_nummer_pkey                   PRIMARY KEY (phone_no);
ALTER TABLE ONLY a23_global_conf                ADD CONSTRAINT global_conf_pkey                     PRIMARY KEY (conf_id);
ALTER TABLE ONLY a23_seeker                     ADD CONSTRAINT mitglied_mitglieds_nr_key            UNIQUE (seeker_no);
ALTER TABLE ONLY a23_seeker                     ADD CONSTRAINT mitglied_pkey                        PRIMARY KEY (seeker_id);
ALTER TABLE ONLY a23_seeker_link_to_stuff       ADD CONSTRAINT mitgliederberufe_pkey                PRIMARY KEY (seeker_stuff_id);
ALTER TABLE ONLY a23_seeker_phone               ADD CONSTRAINT mitglieds_tel_nr_pkey                PRIMARY KEY (phone_id);
ALTER TABLE ONLY a23_provider_pobox             ADD CONSTRAINT postfach_pkey                        PRIMARY KEY (pobox_no);
ALTER TABLE ONLY a23_quality                    ADD CONSTRAINT qualitaeten_merkmal_key              UNIQUE (quality_type);
ALTER TABLE ONLY a23_seeker_link_to_quality     ADD CONSTRAINT qualitaeten_mitglied_pkey            PRIMARY KEY (seeker_quality_id);
ALTER TABLE ONLY a23_quality                    ADD CONSTRAINT qualitaeten_pkey                     PRIMARY KEY (quality_id);
ALTER TABLE ONLY a23_offer_link_to_quality      ADD CONSTRAINT qualitaeten_stelle_pkey              PRIMARY KEY (offer_quality_id);
ALTER TABLE ONLY a23_offer                      ADD CONSTRAINT stelle_pkey                          PRIMARY KEY (offer_id);
ALTER TABLE ONLY a23_offer_link_to_stuff        ADD CONSTRAINT stellen_berufe_pkey                  PRIMARY KEY (offer_stuff_id);


-- ##################### INDEX ####################

CREATE INDEX a23_activity_alarm_time_index                  ON a23_activity                 USING btree (alarm_time);
CREATE INDEX a23_activity_logbook_activity_id_index         ON a23_activity_logbook         USING btree (activity_id);
CREATE INDEX a23_activity_priority_index                    ON a23_activity                 USING btree (priority);
CREATE INDEX a23_activity_time_pressure_index               ON a23_activity                 USING btree (time_pressure);
CREATE INDEX a23_filestore_container_file_id_index          ON a23_filestore_container      USING btree (file_id);
CREATE INDEX a23_filestore_container_tag_id_index           ON a23_filestore_container      USING btree (tag_id);
CREATE INDEX a23_filestore_delete_date_index                ON a23_filestore                USING btree (delete_date);
CREATE INDEX a23_filestore_md5_sum_index                    ON a23_filestore                USING btree (md5_sum);
CREATE INDEX a23_newsletter_log_date_index                  ON a23_newsletter_log           USING btree (create_date);
CREATE INDEX a23_newsletter_log_newsletter_id_index         ON a23_newsletter_log           USING btree (newsletter_id);
CREATE INDEX a23_newsletter_sent_to_seeker_seeker_id_index  ON a23_newsletter_log           USING btree (newsletter_id);
CREATE INDEX a23_provider_black_list_provider_id_index      ON a23_provider_black_list      USING btree (provider_id);
CREATE INDEX a23_provider_member_provider_id_index          ON a23_provider_member          USING btree (provider_id);
CREATE INDEX a23_provider_phone_provider_no_index           ON a23_provider_phone           USING btree (phone_no);
CREATE INDEX a23_provider_provider_id_index                 ON a23_provider                 USING btree (provider_id);
CREATE INDEX a23_request_offer_id_index                     ON a23_request                  USING btree (offer_id);
CREATE INDEX a23_request_seeker_id_index                    ON a23_request                  USING btree (seeker_id);
CREATE INDEX a23_seeker_link_to_handicap_handicap_id_index  ON a23_seeker_link_to_handicap  USING btree (handicap_id);
CREATE INDEX a23_seeker_link_to_handicap_seeker_id_index    ON a23_seeker_link_to_handicap  USING btree (seeker_id);
CREATE INDEX a23_seeker_link_to_quality_quality_id_index    ON a23_seeker_link_to_quality   USING btree (quality_id);
CREATE INDEX a23_seeker_link_to_quality_seeker_id_index     ON a23_seeker_link_to_quality   USING btree (seeker_id);
CREATE INDEX a23_seeker_link_to_stuff_seeker_id_index       ON a23_seeker_link_to_stuff     USING btree (seeker_id);
CREATE INDEX a23_seeker_link_to_stuff_stuff_id_index        ON a23_seeker_link_to_stuff     USING btree (stuff_id);
CREATE INDEX a23_seeker_logbook_mitglied_log_id_index       ON a23_seeker_logbook           USING btree (seeker_id);
CREATE INDEX a23_seeker_seeker_id_index                     ON a23_seeker                   USING btree (seeker_id);


--
-- ########## FK CONSTRAINT #####################################
--

ALTER TABLE ONLY a23_file_reserve
    ADD CONSTRAINT a23_file_reserve_file_id_fkey
    FOREIGN KEY (file_id) REFERENCES a23_filestore(file_id);

ALTER TABLE ONLY a23_file_reserve
    ADD CONSTRAINT a23_file_reserve_mitglieds_id_fkey
    FOREIGN KEY (editor_id) REFERENCES a23_seeker(seeker_id);

ALTER TABLE ONLY a23_newsletter_log
    ADD CONSTRAINT a23_newsletter_log_crm_user_id_fkey
    FOREIGN KEY (editor_id) REFERENCES a23_seeker(seeker_id);

ALTER TABLE ONLY a23_newsletter_sent_to_seeker
    ADD CONSTRAINT a23_newsletter_sent_to_seeker_crm_user_id_fkey
    FOREIGN KEY (seeker_id) REFERENCES a23_seeker(seeker_id);

ALTER TABLE ONLY a23_newsletter_sent_to_seeker
    ADD CONSTRAINT a23_newsletter_sent_to_seeker_newsletter_id_fkey
    FOREIGN KEY (newsletter_id) REFERENCES a23_newsletter_log(newsletter_id);

ALTER TABLE ONLY a23_seeker_logbook
    ADD CONSTRAINT a23_seeker_logbook_autor_id_fkey
    FOREIGN KEY (editor_id) REFERENCES a23_seeker(seeker_id);

ALTER TABLE ONLY a23_seeker_logbook
    ADD CONSTRAINT a23_seeker_logbook_mitglied_id_fkey
    FOREIGN KEY (seeker_id) REFERENCES a23_seeker(seeker_id);

ALTER TABLE ONLY a23_activity_activity
    ADD CONSTRAINT activity_activity_aim_id_fkey
    FOREIGN KEY (aim_id) REFERENCES a23_activity(activity_id);

ALTER TABLE ONLY a23_activity_activity
    ADD CONSTRAINT activity_activity_owner_id_fkey
    FOREIGN KEY (owner_id) REFERENCES a23_activity(activity_id);

ALTER TABLE ONLY a23_activity_container
    ADD CONSTRAINT activity_container_activity_id_fkey
    FOREIGN KEY (activity_id) REFERENCES a23_activity(activity_id);

ALTER TABLE ONLY a23_activity_container
    ADD CONSTRAINT activity_container_container_id_fkey
    FOREIGN KEY (container_id) REFERENCES a23_common_container(common_container_id);

ALTER TABLE ONLY a23_activity_filestore
    ADD CONSTRAINT activity_filestore_activity_id_fkey
    FOREIGN KEY (activity_id) REFERENCES a23_activity(activity_id);

ALTER TABLE ONLY a23_activity_filestore
    ADD CONSTRAINT activity_filestore_filestore_id_fkey
    FOREIGN KEY (filestore_id) REFERENCES a23_filestore(file_id);

ALTER TABLE ONLY a23_activity_provider
    ADD CONSTRAINT activity_firma_activity_id_fkey
    FOREIGN KEY (activity_id) REFERENCES a23_activity(activity_id);

ALTER TABLE ONLY a23_activity_provider
    ADD CONSTRAINT activity_firma_firma_id_fkey
    FOREIGN KEY (provider_id) REFERENCES a23_provider(provider_id);

ALTER TABLE ONLY a23_activity_logbook
    ADD CONSTRAINT activity_logbook_activity_id_fkey
    FOREIGN KEY (activity_id) REFERENCES a23_activity(activity_id);

ALTER TABLE ONLY a23_activity_logbook
    ADD CONSTRAINT activity_logbook_autor_id_fkey
    FOREIGN KEY (editor_id) REFERENCES a23_seeker(seeker_id);

ALTER TABLE ONLY a23_activity_seeker
    ADD CONSTRAINT activity_mitglied_activity_id_fkey
    FOREIGN KEY (activity_id) REFERENCES a23_activity(activity_id);

ALTER TABLE ONLY a23_activity_seeker
    ADD CONSTRAINT activity_mitglied_mitglieds_id_fkey
    FOREIGN KEY (seeker_id) REFERENCES a23_seeker(seeker_id);

ALTER TABLE ONLY a23_request
    ADD CONSTRAINT bewerbung_mitglieds_id_fkey
    FOREIGN KEY (seeker_id) REFERENCES a23_seeker(seeker_id);

ALTER TABLE ONLY a23_request
    ADD CONSTRAINT bewerbung_stellen_id_fkey
    FOREIGN KEY (offer_id) REFERENCES a23_offer(offer_id);

ALTER TABLE ONLY a23_request
    ADD CONSTRAINT bewerbung_vorgangs_bearbeiter_fkey
    FOREIGN KEY (editor_id) REFERENCES a23_seeker(seeker_id);

ALTER TABLE ONLY a23_industry
    ADD CONSTRAINT branchen_kat_firmen_id_fkey
    FOREIGN KEY (provider_id) REFERENCES a23_provider(provider_id);

ALTER TABLE ONLY a23_provider_domain
    ADD CONSTRAINT domain_name_firmen_id_fkey
    FOREIGN KEY (provider_id) REFERENCES a23_provider(provider_id);

ALTER TABLE ONLY a23_seeker_link_to_handicap
    ADD CONSTRAINT einschraenkung_mitglied_merkmal_id_fkey
    FOREIGN KEY (handicap_id) REFERENCES a23_handicap(handicap_id);

ALTER TABLE ONLY a23_seeker_link_to_handicap
    ADD CONSTRAINT einschraenkung_mitglied_mitglieds_id_fkey
    FOREIGN KEY (seeker_id) REFERENCES a23_seeker(seeker_id);

ALTER TABLE ONLY a23_offer_link_to_handicap
    ADD CONSTRAINT einschraenkung_stellen_merkmal_id_fkey
    FOREIGN KEY (handicap_id) REFERENCES a23_handicap(handicap_id);

ALTER TABLE ONLY a23_offer_link_to_handicap
    ADD CONSTRAINT einschraenkung_stellen_stellen_id_fkey
    FOREIGN KEY (offer_id) REFERENCES a23_offer(offer_id);

ALTER TABLE ONLY a23_provider_member_email
    ADD CONSTRAINT email_firmen_id_fkey
    FOREIGN KEY (provider_id) REFERENCES a23_provider(provider_id);

ALTER TABLE ONLY a23_provider_member_email
    ADD CONSTRAINT email_mitarbeiter_id_fkey
    FOREIGN KEY (member_id) REFERENCES a23_provider_member(member_id);

ALTER TABLE ONLY a23_filestore_container
    ADD CONSTRAINT filestore_container_file_id_fkey
    FOREIGN KEY (file_id) REFERENCES a23_filestore(file_id);

ALTER TABLE ONLY a23_filestore_container
    ADD CONSTRAINT filestore_container_tag_id_fkey
    FOREIGN KEY (tag_id) REFERENCES a23_common_container(common_container_id);

ALTER TABLE ONLY a23_filestore
    ADD CONSTRAINT filestore_version_of_id_fkey
    FOREIGN KEY (version_of_id) REFERENCES a23_filestore(file_id);

ALTER TABLE ONLY a23_provider
    ADD CONSTRAINT firma_mutterkonzern_fkey
    FOREIGN KEY (parent_company) REFERENCES a23_provider(provider_id);

ALTER TABLE ONLY a23_provider_black_list
    ADD CONSTRAINT firmen_black_list_firmen_id_fkey
    FOREIGN KEY (provider_id) REFERENCES a23_provider(provider_id);

ALTER TABLE ONLY a23_provider_member
    ADD CONSTRAINT firmen_mitarbeiter_firmen_id_fkey
    FOREIGN KEY (provider_id) REFERENCES a23_provider(provider_id);

ALTER TABLE ONLY a23_provider_member_phone
    ADD CONSTRAINT firmen_mitarbeiter_tel_nr_firmen_id_fkey
    FOREIGN KEY (member_id) REFERENCES a23_provider_member(member_id);

ALTER TABLE ONLY a23_provider_phone
    ADD CONSTRAINT firmen_nummer_firmen_id_fkey
    FOREIGN KEY (provider_id) REFERENCES a23_provider(provider_id);

ALTER TABLE ONLY a23_seeker_link_to_stuff
    ADD CONSTRAINT mitgliederberufe_berufs_id_fkey
    FOREIGN KEY (stuff_id) REFERENCES a23_stuff_type(stuff_id);

ALTER TABLE ONLY a23_seeker_link_to_stuff
    ADD CONSTRAINT mitgliederberufe_mitglieds_id_fkey
    FOREIGN KEY (seeker_id) REFERENCES a23_seeker(seeker_id);

ALTER TABLE ONLY a23_seeker_phone
    ADD CONSTRAINT mitglieds_tel_nr_mitglieds_id_fkey
    FOREIGN KEY (seeker_id) REFERENCES a23_seeker(seeker_id);
ALTER TABLE ONLY a23_provider_pobox
    ADD CONSTRAINT postfach_firmen_id_fkey
    FOREIGN KEY (provider_id) REFERENCES a23_provider(provider_id);
ALTER TABLE ONLY a23_seeker_link_to_quality
    ADD CONSTRAINT qualitaeten_mitglied_merkmal_id_fkey
    FOREIGN KEY (quality_id) REFERENCES a23_quality(quality_id);
ALTER TABLE ONLY a23_seeker_link_to_quality
    ADD CONSTRAINT qualitaeten_mitglied_mitglieds_id_fkey
    FOREIGN KEY (seeker_id) REFERENCES a23_seeker(seeker_id);
ALTER TABLE ONLY a23_offer_link_to_quality
    ADD CONSTRAINT qualitaeten_stelle_merkmal_id_fkey
    FOREIGN KEY (quality_id) REFERENCES a23_quality(quality_id);
ALTER TABLE ONLY a23_offer_link_to_quality
    ADD CONSTRAINT qualitaeten_stelle_stellen_id_fkey
    FOREIGN KEY (offer_id) REFERENCES a23_offer(offer_id);
ALTER TABLE ONLY a23_offer
    ADD CONSTRAINT stelle_firmen_id_fkey
    FOREIGN KEY (provider_id) REFERENCES a23_provider(provider_id);
ALTER TABLE ONLY a23_offer_link_to_stuff
    ADD CONSTRAINT stellen_berufe_berufs_id_fkey
    FOREIGN KEY (stuff_id) REFERENCES a23_stuff_type(stuff_id);
ALTER TABLE ONLY a23_offer_link_to_stuff
    ADD CONSTRAINT stellen_berufe_stellen_id_fkey
    FOREIGN KEY (offer_id) REFERENCES a23_offer(offer_id);

--  ################ Neue Features in 1.0  ################

CREATE TABLE a23_seeker_filestore (
    link_id               SERIAL PRIMARY KEY,
    seeker_id             INTEGER REFERENCES a23_seeker (seeker_id) NOT NULL,
    filestore_id          INTEGER REFERENCES a23_filestore(file_id) UNIQUE NOT NULL
);


COMMENT ON TABLE a23_seeker_filestore
IS 'Verknüpft Dateien mit einem Sucher';
COMMENT ON COLUMN a23_seeker_filestore.seeker_id
IS 'ID des Suchers';
COMMENT ON COLUMN a23_seeker_filestore.filestore_id
IS 'ID einer Datei';



CREATE TABLE a23_provider_filestore (
    link_id               SERIAL PRIMARY KEY,
    provider_id           INTEGER REFERENCES a23_provider (provider_id) NOT NULL,
    filestore_id          INTEGER REFERENCES a23_filestore(file_id) UNIQUE NOT NULL
);


COMMENT ON TABLE a23_provider_filestore
IS 'Verknüpft Dateien mit einem Anbieter';
COMMENT ON COLUMN a23_provider_filestore.provider_id
IS 'ID des Anbieters';
COMMENT ON COLUMN a23_provider_filestore.filestore_id
IS 'ID einer Datei';

-- Neue Spalten zur Aufteilung der Telefonnummer


ALTER TABLE a23_provider_phone ADD COLUMN   country_code TEXT;
UPDATE      a23_provider_phone SET          country_code = ''  WHERE country_code  IS NULL;
ALTER TABLE a23_provider_phone ALTER COLUMN country_code SET NOT NULL;
ALTER TABLE a23_provider_phone ALTER COLUMN country_code SET DEFAULT '';
COMMENT ON COLUMN a23_provider_phone.country_code
IS 'Ländercode';

ALTER TABLE a23_provider_phone ADD COLUMN   area_code TEXT;
UPDATE      a23_provider_phone SET          area_code = ''  WHERE area_code  IS NULL;
ALTER TABLE a23_provider_phone ALTER COLUMN area_code SET NOT NULL;
ALTER TABLE a23_provider_phone ALTER COLUMN area_code SET DEFAULT '';
COMMENT ON COLUMN a23_provider_phone.area_code
IS 'Vorwahl';

ALTER TABLE a23_provider_phone ADD COLUMN direct_inward_dialing TEXT;
UPDATE      a23_provider_phone SET          direct_inward_dialing = ''  WHERE direct_inward_dialing  IS NULL;
ALTER TABLE a23_provider_phone ALTER COLUMN direct_inward_dialing SET NOT NULL;
ALTER TABLE a23_provider_phone ALTER COLUMN direct_inward_dialing SET DEFAULT '';
COMMENT ON COLUMN a23_provider_phone.direct_inward_dialing
IS 'Durchwahl';


ALTER TABLE   a23_provider_member_phone ADD COLUMN   country_code TEXT;
UPDATE        a23_provider_member_phone SET          country_code = ''  WHERE country_code  IS NULL;
ALTER TABLE   a23_provider_member_phone ALTER COLUMN country_code SET NOT NULL;
ALTER TABLE   a23_provider_member_phone ALTER COLUMN country_code SET DEFAULT '';
COMMENT ON COLUMN a23_provider_member_phone.country_code
IS 'Ländercode';

ALTER TABLE   a23_provider_member_phone ADD COLUMN area_code TEXT;
UPDATE        a23_provider_member_phone SET        area_code = ''  WHERE area_code  IS NULL;
ALTER TABLE   a23_provider_member_phone ALTER COLUMN area_code SET NOT NULL;
ALTER TABLE   a23_provider_member_phone ALTER COLUMN area_code SET DEFAULT '';
COMMENT ON COLUMN a23_provider_member_phone.area_code
IS 'Vorwahl';

ALTER TABLE a23_provider_member_phone ADD COLUMN   direct_inward_dialing TEXT;
UPDATE      a23_provider_member_phone SET          direct_inward_dialing = ''  WHERE direct_inward_dialing  IS NULL;
ALTER TABLE a23_provider_member_phone ALTER COLUMN direct_inward_dialing SET NOT NULL;
ALTER TABLE a23_provider_member_phone ALTER COLUMN direct_inward_dialing SET DEFAULT '';
COMMENT ON COLUMN a23_provider_member_phone.direct_inward_dialing
IS 'Durchwahl';

-- Veränderte Nutzung der Telefon-Tabelle des Anbieters - PRIMARY KEY (phone_no) muss weg
ALTER TABLE a23_provider_phone DROP CONSTRAINT firmen_nummer_pkey ;
ALTER TABLE a23_provider_phone ADD COLUMN provider_phone_id SERIAL PRIMARY KEY;
COMMENT ON COLUMN a23_provider_phone.provider_phone_id
IS 'Eindeutige ID der Telefonnummer';

-- Telefonnummer des Suchers bekommt noch ein Bezeichnerfeld


ALTER TABLE   a23_seeker_phone ADD COLUMN   fax_or_phone TEXT;
UPDATE        a23_seeker_phone SET          fax_or_phone = ''  WHERE fax_or_phone  IS NULL;
ALTER TABLE   a23_seeker_phone ALTER COLUMN fax_or_phone SET NOT NULL;
ALTER TABLE   a23_seeker_phone ALTER COLUMN fax_or_phone SET DEFAULT '';
COMMENT ON COLUMN a23_seeker_phone.fax_or_phone
IS 'Bezeichner des Datensatzes (z.B. Büro: Fax: MailTo: etc)';


-- Der Datentyp der Postleitzahl muss geändert werden, damit eine führende
-- Null möglich ist (wie z. B. bei Dresden). So ist jetzt auch D-890 möglich.
ALTER TABLE a23_seeker ALTER COLUMN zip_code TYPE TEXT;
ALTER TABLE a23_provider ALTER COLUMN zip_code TYPE TEXT;

-- Erweiterung der Container

ALTER TABLE   a23_common_container ADD COLUMN   catalog TEXT;
UPDATE        a23_common_container SET          catalog = '[DEFAULT]' WHERE catalog IS NULL;
ALTER TABLE   a23_common_container ALTER COLUMN catalog SET NOT NULL;
ALTER TABLE   a23_common_container ALTER COLUMN catalog SET DEFAULT 'DEFAULT';
COMMENT ON COLUMN a23_common_container.catalog
IS 'Übergeordnente Kategorie/Katalog. Nützlich wenn man viele Container hat.';

-- Tabelle für alle Dinge der Kontaktperson, die nirgendwo Platz fanden.
CREATE TABLE a23_provider_member_misc
(
    misc_id SERIAL PRIMARY KEY,
    misc_type   text    NOT NULL,
    misc_value  text    NOT NULL,
    provider_member_id INTEGER REFERENCES a23_provider_member (member_id) NOT NULL
);

    -- INDEX

    CREATE INDEX a23_provider_member_misc_member_id_index
        ON a23_provider_member_misc(provider_member_id);

    CREATE INDEX a23_provider_member_misc_type_index
        ON a23_provider_member_misc(misc_type);

    -- TABELLEN-DOKU

    COMMENT ON TABLE a23_provider_member_misc IS
        'Tabelle für alle Dinge der Kontaktperson, die nirgendwo Platz fanden.';

    -- SPALTEN-DOKU

    COMMENT ON COLUMN a23_provider_member_misc.misc_type IS
        'Welche Art Sache';
    COMMENT ON COLUMN a23_provider_member_misc.misc_value IS
        'Wert der Sache';
    COMMENT ON COLUMN a23_provider_member_misc.provider_member_id IS
        'ID der Kontaktperson';



-- ################### INSERTS #######################

INSERT INTO a23_seeker
(
    seeker_no,
    seeker_id,
    name,
    street,
    housenumber,
    zip_code,
    city,
    birthday,
    salutation,
    joining,
    priority,
    note,
    address_addition
) VALUES
(
    -1,
    -1,
    'anonymous',
    '',
    '',
    0,
    '',
    DATE'1753-01-01',
    '',
    DATE'now',
    0,
    'Vom System angelegter Sucher für Aktivitäten von Unbekannten',
    ''
);



INSERT INTO a23_version
(
    a23_version_id,
    major_release,
    minor_release,
    patch_level
) VALUES
(
    DEFAULT,
    1,
    0,
    0
);

COMMIT;
