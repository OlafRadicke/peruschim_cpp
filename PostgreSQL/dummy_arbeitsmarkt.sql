--
-- PostgreSQL database dump
--

SET client_encoding = 'UTF8';
SET standard_conforming_strings = off;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET escape_string_warning = off;

--
-- Name: plpgsql; Type: PROCEDURAL LANGUAGE; Schema: -; Owner: -
--

CREATE PROCEDURAL LANGUAGE plpgsql;


SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: a23_activity; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_activity (
    activity_id integer NOT NULL,
    time_pressure integer NOT NULL,
    priority integer NOT NULL,
    alarm_time timestamp without time zone,
    snooze_interval bigint,
    delete_date timestamp without time zone,
    title text NOT NULL,
    note text NOT NULL,
    CONSTRAINT activity_prioritaet_check CHECK (((priority > (-1)) AND (priority < 101))),
    CONSTRAINT activity_zeitdruck_check CHECK (((time_pressure > (-1)) AND (time_pressure < 101)))
);


--
-- Name: TABLE a23_activity; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_activity IS 'Aktivitäten (TODOS) für den Workflow';


--
-- Name: COLUMN a23_activity.activity_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity.activity_id IS 'ID der Aktivität';


--
-- Name: COLUMN a23_activity.time_pressure; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity.time_pressure IS 'Wert von 0 bis 100 % (0 ist wenig / 100 sehr dringlich)';


--
-- Name: COLUMN a23_activity.priority; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity.priority IS 'Wert von 0 bis 100 % (0 unwichtig / 100 sehr wichtig ';


--
-- Name: COLUMN a23_activity.alarm_time; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity.alarm_time IS 'eitpunkt (Datum+Uhrzeit) zu dem erinnert werden soll';


--
-- Name: COLUMN a23_activity.snooze_interval; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity.snooze_interval IS 'Erinnerungs-Intervall (wie ein Timer) in Ticks';


--
-- Name: COLUMN a23_activity.delete_date; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity.delete_date IS 'Zeitstempel der Löschung der Aktivität';


--
-- Name: COLUMN a23_activity.title; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity.title IS 'Überschrift der Aktivität';


--
-- Name: COLUMN a23_activity.note; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity.note IS 'Ausführliche Beschreibung der Aktivität';


--
-- Name: a23_activity_activity; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_activity_activity (
    owner_id integer NOT NULL,
    aim_id integer NOT NULL,
    activity_activity_id integer NOT NULL
);


--
-- Name: TABLE a23_activity_activity; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_activity_activity IS 'Verknüpft Aktivitäten mit Aktivitäten';


--
-- Name: COLUMN a23_activity_activity.owner_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity_activity.owner_id IS 'ID der Aktivität die Eigentümer des Links ist';


--
-- Name: COLUMN a23_activity_activity.aim_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity_activity.aim_id IS 'ID der Aktivität die Ziel des Links ist';


--
-- Name: a23_activity_container; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_activity_container (
    activity_id integer NOT NULL,
    container_id integer NOT NULL,
    activity_container_id integer NOT NULL
);


--
-- Name: TABLE a23_activity_container; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_activity_container IS 'Verknüpft Container mit Aktivitäten';


--
-- Name: COLUMN a23_activity_container.activity_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity_container.activity_id IS 'ID der Aktivität';


--
-- Name: COLUMN a23_activity_container.container_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity_container.container_id IS 'ID eines Containers';


--
-- Name: a23_activity_filestore; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_activity_filestore (
    activity_id integer NOT NULL,
    filestore_id integer NOT NULL,
    activity_filestore_id integer NOT NULL
);


--
-- Name: TABLE a23_activity_filestore; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_activity_filestore IS 'Verknüpft Dateien mit Aktivitäten';


--
-- Name: COLUMN a23_activity_filestore.activity_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity_filestore.activity_id IS 'ID der Aktivität';


--
-- Name: COLUMN a23_activity_filestore.filestore_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity_filestore.filestore_id IS 'ID einer Datei';


--
-- Name: a23_activity_logbook; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_activity_logbook (
    log_id integer NOT NULL,
    activity_id integer NOT NULL,
    editor_id integer NOT NULL,
    time_stamp timestamp without time zone NOT NULL,
    title text NOT NULL,
    note text DEFAULT ''::text NOT NULL
);


--
-- Name: TABLE a23_activity_logbook; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_activity_logbook IS 'Protokollieren/Dokumentieren von Ereignissen';


--
-- Name: COLUMN a23_activity_logbook.log_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity_logbook.log_id IS 'ID des Protokolleintrags';


--
-- Name: COLUMN a23_activity_logbook.activity_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity_logbook.activity_id IS 'ID der des Protokolls der Aktivität';


--
-- Name: COLUMN a23_activity_logbook.editor_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity_logbook.editor_id IS 'Verweis auf eine ID eines Suchers, der der Autor ist.';


--
-- Name: COLUMN a23_activity_logbook.time_stamp; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity_logbook.time_stamp IS 'Erstellungsdatum';


--
-- Name: COLUMN a23_activity_logbook.title; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity_logbook.title IS 'Überschrift des Protokolleintrags';


--
-- Name: COLUMN a23_activity_logbook.note; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity_logbook.note IS 'Die eigentliche Meldung';


--
-- Name: a23_activity_provider; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_activity_provider (
    activity_id integer NOT NULL,
    provider_id integer NOT NULL,
    link_id integer NOT NULL
);


--
-- Name: TABLE a23_activity_provider; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_activity_provider IS 'Verknüpft Anbieter mit Aktivitäten';


--
-- Name: COLUMN a23_activity_provider.activity_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity_provider.activity_id IS 'ID der Aktivität';


--
-- Name: COLUMN a23_activity_provider.provider_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity_provider.provider_id IS 'ID eines Anbieters';


--
-- Name: a23_activity_seeker; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_activity_seeker (
    activity_id integer NOT NULL,
    seeker_id integer NOT NULL,
    link_id integer NOT NULL
);


--
-- Name: TABLE a23_activity_seeker; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_activity_seeker IS 'Verknüpft Sucher mit Aktivitäten';


--
-- Name: COLUMN a23_activity_seeker.activity_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity_seeker.activity_id IS 'ID der Aktivität';


--
-- Name: COLUMN a23_activity_seeker.seeker_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_activity_seeker.seeker_id IS 'ID des Suchers';


--
-- Name: a23_common_container; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_common_container (
    common_container_id integer NOT NULL,
    name text NOT NULL,
    catalog text DEFAULT 'DEFAULT'::text NOT NULL
);


--
-- Name: TABLE a23_common_container; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_common_container IS 'Container-Bezeichner um verschiedene Dinge
        (z. B. Dateien) thematisch zusammenzufassen';


--
-- Name: COLUMN a23_common_container.common_container_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_common_container.common_container_id IS 'ID des Containers';


--
-- Name: COLUMN a23_common_container.name; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_common_container.name IS 'Bezeichner des Containers';


--
-- Name: COLUMN a23_common_container.catalog; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_common_container.catalog IS 'Übergeordnente Kategorie/Katalog. Nützlich wenn man viele Container hat.';


--
-- Name: a23_file_reserve; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_file_reserve (
    file_id integer NOT NULL,
    editor_id integer NOT NULL,
    start_date timestamp without time zone NOT NULL,
    end_date timestamp without time zone NOT NULL,
    note text NOT NULL,
    a23_file_reserve_id integer NOT NULL
);


--
-- Name: TABLE a23_file_reserve; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_file_reserve IS 'Zur Vermeidung von Bearbeitungskonflikten,
        Reservierungen für die Tabelle filestore.';


--
-- Name: COLUMN a23_file_reserve.file_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_file_reserve.file_id IS 'ID der Datei, die reserviert werden soll';


--
-- Name: COLUMN a23_file_reserve.editor_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_file_reserve.editor_id IS 'ID der Person, die eine Reservierung angefordert hat';


--
-- Name: COLUMN a23_file_reserve.start_date; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_file_reserve.start_date IS 'Wann die Reservierung gesetzt wurde';


--
-- Name: COLUMN a23_file_reserve.end_date; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_file_reserve.end_date IS 'Bis wann reserviert wurde';


--
-- Name: COLUMN a23_file_reserve.note; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_file_reserve.note IS 'Erläuterungen und Kommentare zur Reservierung';


--
-- Name: a23_file_reserve_a23_file_reserve_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE a23_file_reserve_a23_file_reserve_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: a23_file_reserve_a23_file_reserve_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE a23_file_reserve_a23_file_reserve_id_seq OWNED BY a23_file_reserve.a23_file_reserve_id;


--
-- Name: a23_file_reserve_a23_file_reserve_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('a23_file_reserve_a23_file_reserve_id_seq', 2, true);


--
-- Name: a23_filestore; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_filestore (
    file_id integer NOT NULL,
    name text DEFAULT ''::text NOT NULL,
    version_of_id integer,
    bin_data bytea NOT NULL,
    version_tag text DEFAULT ''::text NOT NULL,
    md5_sum text NOT NULL,
    create_date timestamp without time zone NOT NULL,
    delete_date timestamp without time zone,
    file_summary text DEFAULT ''::text NOT NULL
);


--
-- Name: TABLE a23_filestore; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_filestore IS 'Tabelle zum Speichern von (Binär-)Dateien';


--
-- Name: COLUMN a23_filestore.file_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_filestore.file_id IS 'ID einer Datei/eines Datensatzes)';


--
-- Name: COLUMN a23_filestore.name; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_filestore.name IS 'Dateiename';


--
-- Name: COLUMN a23_filestore.version_of_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_filestore.version_of_id IS 'Die ID der (alten) Datei die mit dieser eine
        neue Version hat.';


--
-- Name: COLUMN a23_filestore.bin_data; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_filestore.bin_data IS 'Die gespeicherten Binär-Daten';


--
-- Name: COLUMN a23_filestore.version_tag; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_filestore.version_tag IS 'Name der Version zur besseren Wiedererkennung
        (z. B. eine Nummer)';


--
-- Name: COLUMN a23_filestore.md5_sum; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_filestore.md5_sum IS 'MD5-Summe (zur Duplikatsuche)';


--
-- Name: COLUMN a23_filestore.create_date; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_filestore.create_date IS 'Erstellungsdatum';


--
-- Name: COLUMN a23_filestore.delete_date; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_filestore.delete_date IS 'Löschdatum (z. B. beim Ersetzen durch neue Version)';


--
-- Name: COLUMN a23_filestore.file_summary; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_filestore.file_summary IS 'Beschreibungstext zur gespeicherten Datei';


--
-- Name: a23_filestore_container; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_filestore_container (
    tag_id integer NOT NULL,
    file_id integer NOT NULL,
    filestore_container_id integer NOT NULL
);


--
-- Name: TABLE a23_filestore_container; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_filestore_container IS 'Zuordnung von Dateien in Containern';


--
-- Name: COLUMN a23_filestore_container.tag_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_filestore_container.tag_id IS 'Verweis auf die ID eines existierenden Containers';


--
-- Name: COLUMN a23_filestore_container.file_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_filestore_container.file_id IS 'Verweis auf die ID einer existierenden Datei';


--
-- Name: a23_global_conf; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_global_conf (
    conf_id integer NOT NULL,
    name_space text NOT NULL,
    conf_type text NOT NULL,
    conf_value text NOT NULL
);


--
-- Name: TABLE a23_global_conf; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_global_conf IS 'Tabelle für globalen Konfigurationsparameter,
        die mehere User benutzen.';


--
-- Name: COLUMN a23_global_conf.conf_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_global_conf.conf_id IS 'ID eines Wertes';


--
-- Name: COLUMN a23_global_conf.name_space; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_global_conf.name_space IS 'Zum Gruppieren von gespeicherten Werten';


--
-- Name: COLUMN a23_global_conf.conf_type; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_global_conf.conf_type IS 'Bezeichner für einen Wert';


--
-- Name: COLUMN a23_global_conf.conf_value; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_global_conf.conf_value IS 'Der eigentliche Wert';


--
-- Name: a23_handicap; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_handicap (
    handicap_type text NOT NULL,
    handicap_id integer NOT NULL
);


--
-- Name: TABLE a23_handicap; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_handicap IS 'Einschränkungen und ihre IDs für Angebote und Sucher';


--
-- Name: COLUMN a23_handicap.handicap_type; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_handicap.handicap_type IS 'Bezeichner einer Einschränkung';


--
-- Name: COLUMN a23_handicap.handicap_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_handicap.handicap_id IS 'ID der Einschränkung';


--
-- Name: a23_industry; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_industry (
    provider_id integer NOT NULL,
    industry_identifier text NOT NULL,
    industry_id integer NOT NULL
);


--
-- Name: TABLE a23_industry; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_industry IS 'Für Zuordnung eines Anbieters zu einer Branche';


--
-- Name: COLUMN a23_industry.provider_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_industry.provider_id IS 'Verweis auf einen existierenden Anbieter';


--
-- Name: COLUMN a23_industry.industry_identifier; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_industry.industry_identifier IS 'Firma kann beliebig vielen Branchen angehören.';


--
-- Name: a23_newsletter_log; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_newsletter_log (
    newsletter_id integer NOT NULL,
    subject text NOT NULL,
    newsletter_body text NOT NULL,
    sent_from text NOT NULL,
    create_date timestamp without time zone NOT NULL,
    editor_id integer NOT NULL
);


--
-- Name: TABLE a23_newsletter_log; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_newsletter_log IS 'Verschickter Newsletter';


--
-- Name: COLUMN a23_newsletter_log.newsletter_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_newsletter_log.newsletter_id IS 'ID des Newsletters';


--
-- Name: COLUMN a23_newsletter_log.subject; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_newsletter_log.subject IS 'Betreff des Newsletters';


--
-- Name: COLUMN a23_newsletter_log.newsletter_body; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_newsletter_log.newsletter_body IS 'Text des Newsletters';


--
-- Name: COLUMN a23_newsletter_log.sent_from; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_newsletter_log.sent_from IS 'Absendeadresse';


--
-- Name: COLUMN a23_newsletter_log.create_date; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_newsletter_log.create_date IS 'Zeitstempel';


--
-- Name: COLUMN a23_newsletter_log.editor_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_newsletter_log.editor_id IS 'ID des Sachbearbeiters, der den Newsletter versendet.';


--
-- Name: a23_newsletter_log_newsletter_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE a23_newsletter_log_newsletter_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: a23_newsletter_log_newsletter_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE a23_newsletter_log_newsletter_id_seq OWNED BY a23_newsletter_log.newsletter_id;


--
-- Name: a23_newsletter_log_newsletter_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('a23_newsletter_log_newsletter_id_seq', 16, true);


--
-- Name: a23_newsletter_sent_to_seeker; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_newsletter_sent_to_seeker (
    newsletter_id integer NOT NULL,
    mail_address text NOT NULL,
    seeker_id integer NOT NULL,
    a23_newsletter_sent_to_seeker_id integer NOT NULL
);


--
-- Name: TABLE a23_newsletter_sent_to_seeker; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_newsletter_sent_to_seeker IS 'Verknüpft Newsletter mit dem Sachbearbeiter, der er ihn erhalten hat.';


--
-- Name: COLUMN a23_newsletter_sent_to_seeker.newsletter_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_newsletter_sent_to_seeker.newsletter_id IS 'ID des Newsletters';


--
-- Name: COLUMN a23_newsletter_sent_to_seeker.mail_address; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_newsletter_sent_to_seeker.mail_address IS 'Die E-Mail-Adresse, an die verschickt wurde.';


--
-- Name: COLUMN a23_newsletter_sent_to_seeker.seeker_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_newsletter_sent_to_seeker.seeker_id IS 'Der Sucher, der eine Newsletter erhalten hat.';


--
-- Name: a23_newsletter_sent_to_seeker_a23_newsletter_sent_to_seeker_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE a23_newsletter_sent_to_seeker_a23_newsletter_sent_to_seeker_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: a23_newsletter_sent_to_seeker_a23_newsletter_sent_to_seeker_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE a23_newsletter_sent_to_seeker_a23_newsletter_sent_to_seeker_seq OWNED BY a23_newsletter_sent_to_seeker.a23_newsletter_sent_to_seeker_id;


--
-- Name: a23_newsletter_sent_to_seeker_a23_newsletter_sent_to_seeker_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('a23_newsletter_sent_to_seeker_a23_newsletter_sent_to_seeker_seq', 1, false);


--
-- Name: a23_offer; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_offer (
    offer_id integer NOT NULL,
    offers_date date DEFAULT '2009-02-21'::date NOT NULL,
    info_source text DEFAULT ''::text NOT NULL,
    provider_id integer NOT NULL,
    job_count integer DEFAULT 1 NOT NULL,
    salutation text DEFAULT ''::text NOT NULL,
    note text DEFAULT ''::text NOT NULL
);


--
-- Name: TABLE a23_offer; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_offer IS 'Tabelle für Angebote/Annoncen';


--
-- Name: COLUMN a23_offer.offer_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_offer.offer_id IS 'Eindeutige, fortlaufende ID-Nummer';


--
-- Name: COLUMN a23_offer.offers_date; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_offer.offers_date IS 'Von wann das Angebot ist';


--
-- Name: COLUMN a23_offer.info_source; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_offer.info_source IS 'Wo das Angebot her ist (z. B. Zeitungsname)';


--
-- Name: COLUMN a23_offer.provider_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_offer.provider_id IS 'Verweis auf einen existierenden Anbieter';


--
-- Name: COLUMN a23_offer.job_count; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_offer.job_count IS 'Wieviel von etwas Angeboten wird';


--
-- Name: COLUMN a23_offer.salutation; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_offer.salutation IS 'Anrede in Form von /Herr/, /Frau/ usw.';


--
-- Name: COLUMN a23_offer.note; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_offer.note IS 'Notizen und Ergänzungen';


--
-- Name: a23_offer_link_to_handicap; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_offer_link_to_handicap (
    offer_id integer NOT NULL,
    handicap_id integer NOT NULL,
    offer_handicap_id integer NOT NULL
);


--
-- Name: TABLE a23_offer_link_to_handicap; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_offer_link_to_handicap IS 'Zuordnung der Einschränkungen zu Angeboten (z. B. keine Schichtarbeit)';


--
-- Name: COLUMN a23_offer_link_to_handicap.offer_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_offer_link_to_handicap.offer_id IS 'ID eines Angebots';


--
-- Name: COLUMN a23_offer_link_to_handicap.handicap_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_offer_link_to_handicap.handicap_id IS 'ID einer Einschränkung';


--
-- Name: a23_offer_link_to_quality; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_offer_link_to_quality (
    offer_id integer NOT NULL,
    quality_id integer NOT NULL,
    offer_quality_id integer NOT NULL
);


--
-- Name: TABLE a23_offer_link_to_quality; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_offer_link_to_quality IS 'Zuordnung von Angeboten zu positiven Merkmalen ("Qualitäten") ';


--
-- Name: COLUMN a23_offer_link_to_quality.offer_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_offer_link_to_quality.offer_id IS 'ID einer Stelle';


--
-- Name: COLUMN a23_offer_link_to_quality.quality_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_offer_link_to_quality.quality_id IS 'ID einer Qualität';


--
-- Name: a23_offer_link_to_stuff; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_offer_link_to_stuff (
    stuff_id integer NOT NULL,
    offer_id integer NOT NULL,
    offer_stuff_id integer NOT NULL
);


--
-- Name: TABLE a23_offer_link_to_stuff; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_offer_link_to_stuff IS 'Verknüpfung von Angeboten mit Eigenschaften';


--
-- Name: COLUMN a23_offer_link_to_stuff.stuff_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_offer_link_to_stuff.stuff_id IS 'ID einer Eigenschaft';


--
-- Name: COLUMN a23_offer_link_to_stuff.offer_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_offer_link_to_stuff.offer_id IS 'ID eines Angebots';


--
-- Name: a23_provider; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_provider (
    provider_id integer NOT NULL,
    district text DEFAULT ''::text NOT NULL,
    name text,
    street text DEFAULT ''::text NOT NULL,
    housenumber text DEFAULT ''::text NOT NULL,
    zip_code text DEFAULT 0 NOT NULL,
    city text DEFAULT ''::text NOT NULL,
    member_count integer DEFAULT 1 NOT NULL,
    parent_company integer,
    note text DEFAULT ''::text NOT NULL
);


--
-- Name: TABLE a23_provider; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_provider IS 'Tabelle für Stammdaten der Anbieter.';


--
-- Name: COLUMN a23_provider.provider_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider.provider_id IS 'Eindeutige ID, die sich nicht mehe ändern sollte.';


--
-- Name: COLUMN a23_provider.district; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider.district IS 'Frei wählbar, um Anbieter geografisch einzuordnen.';


--
-- Name: COLUMN a23_provider.name; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider.name IS 'Name des Anbiters (keine Differenzierung Vor- und Zuname).';


--
-- Name: COLUMN a23_provider.street; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider.street IS 'Straße der Adresse des Anbieters';


--
-- Name: COLUMN a23_provider.housenumber; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider.housenumber IS 'Hausnummer der Adresse des Anbieters.';


--
-- Name: COLUMN a23_provider.zip_code; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider.zip_code IS 'Postleitzahl der Adresse des Anbieters';


--
-- Name: COLUMN a23_provider.city; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider.city IS 'Ort der Adresse des Anbieters.';


--
-- Name: COLUMN a23_provider.member_count; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider.member_count IS 'Mitarbeiteranzahl eines Anbiters';


--
-- Name: COLUMN a23_provider.parent_company; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider.parent_company IS 'Verweis auf einen anderen Anbieter, wenn
        dieser dem einen untersteht oder dazugehört.';


--
-- Name: COLUMN a23_provider.note; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider.note IS 'Notizen und Vermerke.';


--
-- Name: a23_provider_black_list; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_provider_black_list (
    provider_id integer NOT NULL,
    provider_black_list_id integer NOT NULL
);


--
-- Name: TABLE a23_provider_black_list; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_provider_black_list IS 'Anbieter die gesperrt sind und nicht berücksichtigt
        werden sollen.';


--
-- Name: COLUMN a23_provider_black_list.provider_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_black_list.provider_id IS 'ID eines gesperrten Anbieters';


--
-- Name: a23_provider_domain; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_provider_domain (
    provider_id integer NOT NULL,
    domain_name text NOT NULL
);


--
-- Name: TABLE a23_provider_domain; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_provider_domain IS 'Zuordnungen einer Internet-Domain zu einem Anbieter';


--
-- Name: COLUMN a23_provider_domain.provider_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_domain.provider_id IS 'Verweis auf einen existierenden Anbieter';


--
-- Name: COLUMN a23_provider_domain.domain_name; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_domain.domain_name IS 'Internet-Domain die nur einmal vorkommen darf.';


--
-- Name: a23_provider_filestore; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_provider_filestore (
    link_id integer NOT NULL,
    provider_id integer NOT NULL,
    filestore_id integer NOT NULL
);


--
-- Name: TABLE a23_provider_filestore; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_provider_filestore IS 'Verknüpft Dateien mit einem Anbieter';


--
-- Name: COLUMN a23_provider_filestore.provider_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_filestore.provider_id IS 'ID des Anbieters';


--
-- Name: COLUMN a23_provider_filestore.filestore_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_filestore.filestore_id IS 'ID einer Datei';


--
-- Name: a23_provider_filestore_link_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE a23_provider_filestore_link_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: a23_provider_filestore_link_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE a23_provider_filestore_link_id_seq OWNED BY a23_provider_filestore.link_id;


--
-- Name: a23_provider_filestore_link_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('a23_provider_filestore_link_id_seq', 1, false);


--
-- Name: a23_provider_member; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_provider_member (
    provider_id integer NOT NULL,
    member_id integer NOT NULL,
    name text NOT NULL,
    department text DEFAULT ''::text NOT NULL,
    task text DEFAULT ''::text NOT NULL,
    consultation_hours text DEFAULT ''::text NOT NULL,
    absence text DEFAULT ''::text NOT NULL,
    note text DEFAULT ''::text NOT NULL
);


--
-- Name: TABLE a23_provider_member; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_provider_member IS 'Informationen zu Ansprechpartnern von Anbietern';


--
-- Name: COLUMN a23_provider_member.provider_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_member.provider_id IS 'Anbieter zu der die Kontaktperson gehört';


--
-- Name: COLUMN a23_provider_member.member_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_member.member_id IS 'Eindeutige, fortlaufende ID für die Kontaktperson';


--
-- Name: COLUMN a23_provider_member.name; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_member.name IS 'Feld für Zu-und Vorname';


--
-- Name: COLUMN a23_provider_member.department; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_member.department IS 'Falls vorhanden Abteilung/Filiale';


--
-- Name: COLUMN a23_provider_member.task; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_member.task IS 'Aufgabe oder Position der Kontaktperson';


--
-- Name: COLUMN a23_provider_member.consultation_hours; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_member.consultation_hours IS 'Vermerk über Anwesenheit';


--
-- Name: COLUMN a23_provider_member.absence; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_member.absence IS 'Vermerk über Abwesenheitszeiten';


--
-- Name: COLUMN a23_provider_member.note; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_member.note IS 'Anmerkungen und Notizen';


--
-- Name: a23_provider_member_email; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_provider_member_email (
    provider_id integer,
    member_id integer,
    email_local_part text DEFAULT ''::text NOT NULL,
    email_domain text DEFAULT ''::text NOT NULL,
    email_id integer NOT NULL
);


--
-- Name: TABLE a23_provider_member_email; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_provider_member_email IS 'Zuordnung von E-Mail-Adressen zu Ansprechpartnern';


--
-- Name: COLUMN a23_provider_member_email.provider_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_member_email.provider_id IS 'ID eines eines Anbieters';


--
-- Name: COLUMN a23_provider_member_email.member_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_member_email.member_id IS 'ID eines Ansprechpartnes eines Anbieters';


--
-- Name: COLUMN a23_provider_member_email.email_local_part; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_member_email.email_local_part IS 'Der Teil der E-Mail-Adresse, der vor "@" steht
        ("peter" von peter@muster-firma.com).';


--
-- Name: COLUMN a23_provider_member_email.email_domain; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_member_email.email_domain IS 'Der Teil der E-Mail-Adresse, der nach "@" steht
        ("muster-firma.com" von peter@muster-firma.com).';


--
-- Name: a23_provider_member_phone; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_provider_member_phone (
    member_id integer NOT NULL,
    phone_no text DEFAULT ''::text NOT NULL,
    fax_or_phone text DEFAULT ''::text NOT NULL,
    phone_id integer NOT NULL,
    country_code text DEFAULT ''::text NOT NULL,
    area_code text DEFAULT ''::text NOT NULL,
    direct_inward_dialing text DEFAULT ''::text NOT NULL
);


--
-- Name: TABLE a23_provider_member_phone; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_provider_member_phone IS 'Zuordnung von Tel.-Nummern zu Anbieter-Ansprechpartnern';


--
-- Name: COLUMN a23_provider_member_phone.member_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_member_phone.member_id IS 'ID eines Ansprechpartnes eines Anbieters (Tabellenbezeichner ist noch irreführend!)';


--
-- Name: COLUMN a23_provider_member_phone.phone_no; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_member_phone.phone_no IS 'Die Nummer des Mitarbeiters';


--
-- Name: COLUMN a23_provider_member_phone.fax_or_phone; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_member_phone.fax_or_phone IS 'Der Bezeichner: Tel, Fax, ICQ, usw.';


--
-- Name: COLUMN a23_provider_member_phone.country_code; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_member_phone.country_code IS 'Ländercode';


--
-- Name: COLUMN a23_provider_member_phone.area_code; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_member_phone.area_code IS 'Vorwahl';


--
-- Name: COLUMN a23_provider_member_phone.direct_inward_dialing; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_member_phone.direct_inward_dialing IS 'Durchwahl';


--
-- Name: a23_provider_phone; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_provider_phone (
    provider_id integer NOT NULL,
    phone_no text NOT NULL,
    fax_or_phone text NOT NULL,
    country_code text DEFAULT ''::text NOT NULL,
    area_code text DEFAULT ''::text NOT NULL,
    direct_inward_dialing text DEFAULT ''::text NOT NULL,
    provider_phone_id integer NOT NULL
);


--
-- Name: TABLE a23_provider_phone; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_provider_phone IS 'Zuordnung einer Tel.- oder Fax-Nummer zu einem Anbieter';


--
-- Name: COLUMN a23_provider_phone.provider_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_phone.provider_id IS 'Verweis auf einen existierenden Anbieter';


--
-- Name: COLUMN a23_provider_phone.phone_no; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_phone.phone_no IS 'Eine Nummer kann immer nur einem Anbieter gehören,
        aber ein Anbieter kann mehrere Nummern haben.';


--
-- Name: COLUMN a23_provider_phone.fax_or_phone; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_phone.fax_or_phone IS 'Ob es sich um eine Tel.- oder Fax-Nummer oder
        etwas anderes handelt.';


--
-- Name: COLUMN a23_provider_phone.country_code; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_phone.country_code IS 'Ländercode';


--
-- Name: COLUMN a23_provider_phone.area_code; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_phone.area_code IS 'Vorwahl';


--
-- Name: COLUMN a23_provider_phone.direct_inward_dialing; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_phone.direct_inward_dialing IS 'Durchwahl';


--
-- Name: COLUMN a23_provider_phone.provider_phone_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_phone.provider_phone_id IS 'Eindeutige ID der Telefonnummer';


--
-- Name: a23_provider_phone_provider_phone_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE a23_provider_phone_provider_phone_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: a23_provider_phone_provider_phone_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE a23_provider_phone_provider_phone_id_seq OWNED BY a23_provider_phone.provider_phone_id;


--
-- Name: a23_provider_phone_provider_phone_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('a23_provider_phone_provider_phone_id_seq', 8, true);


--
-- Name: a23_provider_pobox; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_provider_pobox (
    provider_id integer NOT NULL,
    pobox_no text NOT NULL
);


--
-- Name: TABLE a23_provider_pobox; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_provider_pobox IS 'Zuordnung der Postfachnummern des Anbieters';


--
-- Name: COLUMN a23_provider_pobox.provider_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_pobox.provider_id IS 'Verweis auf einen existierenden Anbieter';


--
-- Name: COLUMN a23_provider_pobox.pobox_no; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_provider_pobox.pobox_no IS 'Postfachanschrift - darf nur einer Firma gehören.';


--
-- Name: a23_quality; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_quality (
    quality_type text NOT NULL,
    quality_id integer NOT NULL
);


--
-- Name: TABLE a23_quality; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_quality IS 'Qualitäten und ihre IDs (z. B. für Führerschein-Klassen)';


--
-- Name: COLUMN a23_quality.quality_type; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_quality.quality_type IS 'Bezeichner der Qualität';


--
-- Name: COLUMN a23_quality.quality_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_quality.quality_id IS 'ID der Qualität';


--
-- Name: a23_request; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_request (
    seeker_id integer,
    editor_id integer,
    request_id integer NOT NULL,
    request_date date DEFAULT '2009-02-21'::date NOT NULL,
    situation text DEFAULT 'no defined'::text NOT NULL,
    note text DEFAULT ''::text NOT NULL,
    offer_id integer NOT NULL
);


--
-- Name: TABLE a23_request; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_request IS 'Tabelle für Kontaktaufnahmen, die an Anbieter rausgegingen.';


--
-- Name: COLUMN a23_request.seeker_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_request.seeker_id IS 'Sucher der den Kontakt hergestellt hat oder für
        den er hergestellt wurde.';


--
-- Name: COLUMN a23_request.editor_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_request.editor_id IS 'Derjenige, der die Kontaktaufnahme bearbeitet/erstellt hat.';


--
-- Name: COLUMN a23_request.request_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_request.request_id IS 'Fortlaufende, eindeutige Nummer';


--
-- Name: COLUMN a23_request.request_date; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_request.request_date IS 'Erstellungsdatum';


--
-- Name: COLUMN a23_request.situation; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_request.situation IS 'In welchen Stadium sich der Kontakt befindet';


--
-- Name: COLUMN a23_request.note; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_request.note IS 'Kommentare und Anmerkungen';


--
-- Name: COLUMN a23_request.offer_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_request.offer_id IS 'Das Angebot, auf das sich der Kontakt bezieht.';


--
-- Name: a23_seeker; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_seeker (
    seeker_no text,
    seeker_id integer NOT NULL,
    name text NOT NULL,
    street text DEFAULT ''::text NOT NULL,
    housenumber text DEFAULT ''::text NOT NULL,
    zip_code text DEFAULT 0 NOT NULL,
    city text DEFAULT ''::text NOT NULL,
    birthday date DEFAULT '1753-01-01'::date NOT NULL,
    salutation text DEFAULT ''::text NOT NULL,
    joining date DEFAULT '2009-02-21'::date NOT NULL,
    priority integer DEFAULT 50 NOT NULL,
    note text DEFAULT ''::text NOT NULL,
    address_addition text DEFAULT ''::text NOT NULL
);


--
-- Name: TABLE a23_seeker; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_seeker IS 'In dieser Tabelle werden die Stammdaten des Suchers gespeichert.';


--
-- Name: COLUMN a23_seeker.seeker_no; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker.seeker_no IS 'Ist eine interne, frei wählbare Verwaltungsnummer.
        Könnte sich mal ändern (z. B. wegen Umzug oder
        Abteilungswechsel).';


--
-- Name: COLUMN a23_seeker.seeker_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker.seeker_id IS 'Eindeutige ID-Nummer, die statisch verwendet werden soll';


--
-- Name: COLUMN a23_seeker.name; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker.name IS 'Name des Suchers. Nach- und Vorname sollte Komma-getrennt
        sein. Nachname zuerst';


--
-- Name: COLUMN a23_seeker.street; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker.street IS 'Straße der Postanschrift';


--
-- Name: COLUMN a23_seeker.housenumber; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker.housenumber IS 'Hausnummer der Postanschrift';


--
-- Name: COLUMN a23_seeker.zip_code; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker.zip_code IS 'Postleitzahl der Postanschrift';


--
-- Name: COLUMN a23_seeker.city; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker.city IS 'Ort der Postanschrift';


--
-- Name: COLUMN a23_seeker.birthday; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker.birthday IS 'Geburtsdatum des Suchers';


--
-- Name: COLUMN a23_seeker.salutation; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker.salutation IS 'Anrede des Suchers: Herr, Frau, Firma, Familie usw.';


--
-- Name: COLUMN a23_seeker.joining; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker.joining IS 'Meint Erfassungsdatum am...';


--
-- Name: COLUMN a23_seeker.priority; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker.priority IS 'Ob der Sucher bei der Suche bevorzugt werden soll,
        um z. B. mehr beworben zu werden.';


--
-- Name: COLUMN a23_seeker.note; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker.note IS 'Sonstige Anmerkungen....';


--
-- Name: COLUMN a23_seeker.address_addition; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker.address_addition IS 'Adresszusätze wie etwa Land';


--
-- Name: a23_seeker_filestore; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_seeker_filestore (
    link_id integer NOT NULL,
    seeker_id integer NOT NULL,
    filestore_id integer NOT NULL
);


--
-- Name: TABLE a23_seeker_filestore; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_seeker_filestore IS 'Verknüpft Dateien mit einem Sucher';


--
-- Name: COLUMN a23_seeker_filestore.seeker_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker_filestore.seeker_id IS 'ID des Suchers';


--
-- Name: COLUMN a23_seeker_filestore.filestore_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker_filestore.filestore_id IS 'ID einer Datei';


--
-- Name: a23_seeker_filestore_link_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE a23_seeker_filestore_link_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: a23_seeker_filestore_link_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE a23_seeker_filestore_link_id_seq OWNED BY a23_seeker_filestore.link_id;


--
-- Name: a23_seeker_filestore_link_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('a23_seeker_filestore_link_id_seq', 1, false);


--
-- Name: a23_seeker_link_to_handicap; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_seeker_link_to_handicap (
    seeker_id integer NOT NULL,
    handicap_id integer NOT NULL,
    seeker_handicap_id integer NOT NULL
);


--
-- Name: TABLE a23_seeker_link_to_handicap; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_seeker_link_to_handicap IS 'Zuordnung der Einschränkungen zu Suchern (z. B. keine Schichtarbeit)';


--
-- Name: COLUMN a23_seeker_link_to_handicap.seeker_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker_link_to_handicap.seeker_id IS 'ID eines Suchers';


--
-- Name: COLUMN a23_seeker_link_to_handicap.handicap_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker_link_to_handicap.handicap_id IS 'ID einer Einschränkung';


--
-- Name: a23_seeker_link_to_quality; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_seeker_link_to_quality (
    seeker_id integer NOT NULL,
    quality_id integer NOT NULL,
    seeker_quality_id integer NOT NULL
);


--
-- Name: TABLE a23_seeker_link_to_quality; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_seeker_link_to_quality IS 'Zuordnung von Suchern zu positiven Merkmalen ("Qualitäten")';


--
-- Name: COLUMN a23_seeker_link_to_quality.seeker_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker_link_to_quality.seeker_id IS 'ID eines Suchers';


--
-- Name: COLUMN a23_seeker_link_to_quality.quality_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker_link_to_quality.quality_id IS 'ID einer Qualität';


--
-- Name: a23_seeker_link_to_stuff; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_seeker_link_to_stuff (
    stuff_id integer NOT NULL,
    seeker_id integer NOT NULL,
    seeker_stuff_id integer NOT NULL
);


--
-- Name: TABLE a23_seeker_link_to_stuff; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_seeker_link_to_stuff IS 'Verknüpfung von Eigenschaften mit Suchern';


--
-- Name: COLUMN a23_seeker_link_to_stuff.stuff_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker_link_to_stuff.stuff_id IS 'ID einer Eigenschaft z.B. Beruf';


--
-- Name: COLUMN a23_seeker_link_to_stuff.seeker_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker_link_to_stuff.seeker_id IS 'ID eines Suchers';


--
-- Name: a23_seeker_logbook; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_seeker_logbook (
    log_id integer NOT NULL,
    seeker_id integer NOT NULL,
    editor_id integer NOT NULL,
    time_stamp timestamp without time zone NOT NULL,
    title text NOT NULL,
    note text DEFAULT ''::text NOT NULL
);


--
-- Name: TABLE a23_seeker_logbook; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_seeker_logbook IS 'Protokollieren/Dokumentieren von Sucher-Ereignissen';


--
-- Name: COLUMN a23_seeker_logbook.log_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker_logbook.log_id IS 'ID des Protokoll-Eintrags';


--
-- Name: COLUMN a23_seeker_logbook.seeker_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker_logbook.seeker_id IS 'ID/Sucher zum Protokoll';


--
-- Name: COLUMN a23_seeker_logbook.editor_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker_logbook.editor_id IS 'Verweis auf die ID/Sucher des Autors';


--
-- Name: COLUMN a23_seeker_logbook.time_stamp; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker_logbook.time_stamp IS 'Erstellungsdatum';


--
-- Name: COLUMN a23_seeker_logbook.title; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker_logbook.title IS 'Überschrift des Protokoll-Eintrags';


--
-- Name: COLUMN a23_seeker_logbook.note; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker_logbook.note IS 'Die eigentliche Meldung';


--
-- Name: a23_seeker_logbook_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE a23_seeker_logbook_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: a23_seeker_logbook_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE a23_seeker_logbook_id_seq OWNED BY a23_seeker_logbook.log_id;


--
-- Name: a23_seeker_logbook_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('a23_seeker_logbook_id_seq', 1, false);


--
-- Name: a23_seeker_phone; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_seeker_phone (
    seeker_id integer,
    phone_no text DEFAULT ''::text NOT NULL,
    phone_id integer NOT NULL,
    fax_or_phone text DEFAULT ''::text NOT NULL
);


--
-- Name: TABLE a23_seeker_phone; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_seeker_phone IS 'Telefonnummern der Sucher';


--
-- Name: COLUMN a23_seeker_phone.seeker_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker_phone.seeker_id IS 'ID eines Suchers';


--
-- Name: COLUMN a23_seeker_phone.phone_no; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker_phone.phone_no IS 'Nummer des Sucher';


--
-- Name: COLUMN a23_seeker_phone.fax_or_phone; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_seeker_phone.fax_or_phone IS 'Bezeichner des Datensatzes (z.B. Büro: Fax: MailTo: etc)';


--
-- Name: a23_stuff_type; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_stuff_type (
    stuff_id integer NOT NULL,
    stuff_type text
);


--
-- Name: TABLE a23_stuff_type; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_stuff_type IS 'Eigenschaftsbezeichnungen  z.B. Berufbezeichnung mit eindeutigen IDs';


--
-- Name: COLUMN a23_stuff_type.stuff_id; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_stuff_type.stuff_id IS 'ID einer Eigenschaft';


--
-- Name: COLUMN a23_stuff_type.stuff_type; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN a23_stuff_type.stuff_type IS 'Der Bezeichner der Eigenschaft z.B. Beruf';


--
-- Name: a23_version; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE a23_version (
    major_release integer NOT NULL,
    minor_release integer NOT NULL,
    patch_level integer NOT NULL,
    a23_version_id integer NOT NULL
);


--
-- Name: TABLE a23_version; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON TABLE a23_version IS 'Tabelle speichert die Programmversion für die die Tabelle erstellt wurde.';


--
-- Name: a23_version_a23_version_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE a23_version_a23_version_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: a23_version_a23_version_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE a23_version_a23_version_id_seq OWNED BY a23_version.a23_version_id;


--
-- Name: a23_version_a23_version_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('a23_version_a23_version_id_seq', 9, true);


--
-- Name: activity_activity_activity_activity_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE activity_activity_activity_activity_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: activity_activity_activity_activity_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE activity_activity_activity_activity_id_seq OWNED BY a23_activity_activity.activity_activity_id;


--
-- Name: activity_activity_activity_activity_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('activity_activity_activity_activity_id_seq', 1, true);


--
-- Name: activity_container_activity_container_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE activity_container_activity_container_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: activity_container_activity_container_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE activity_container_activity_container_id_seq OWNED BY a23_activity_container.activity_container_id;


--
-- Name: activity_container_activity_container_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('activity_container_activity_container_id_seq', 1, false);


--
-- Name: activity_filestore_activity_filestore_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE activity_filestore_activity_filestore_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: activity_filestore_activity_filestore_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE activity_filestore_activity_filestore_id_seq OWNED BY a23_activity_filestore.activity_filestore_id;


--
-- Name: activity_filestore_activity_filestore_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('activity_filestore_activity_filestore_id_seq', 3, true);


--
-- Name: activity_firma_activity_firma_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE activity_firma_activity_firma_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: activity_firma_activity_firma_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE activity_firma_activity_firma_id_seq OWNED BY a23_activity_provider.link_id;


--
-- Name: activity_firma_activity_firma_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('activity_firma_activity_firma_id_seq', 1, true);


--
-- Name: activity_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE activity_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: activity_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE activity_id_seq OWNED BY a23_activity.activity_id;


--
-- Name: activity_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('activity_id_seq', 4, true);


--
-- Name: activity_logbook_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE activity_logbook_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: activity_logbook_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE activity_logbook_id_seq OWNED BY a23_activity_logbook.log_id;


--
-- Name: activity_logbook_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('activity_logbook_id_seq', 1, true);


--
-- Name: activity_mitglied_activity_mitglied_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE activity_mitglied_activity_mitglied_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: activity_mitglied_activity_mitglied_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE activity_mitglied_activity_mitglied_id_seq OWNED BY a23_activity_seeker.link_id;


--
-- Name: activity_mitglied_activity_mitglied_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('activity_mitglied_activity_mitglied_id_seq', 2, true);


--
-- Name: beruf_berufs_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE beruf_berufs_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: beruf_berufs_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE beruf_berufs_id_seq OWNED BY a23_stuff_type.stuff_id;


--
-- Name: beruf_berufs_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('beruf_berufs_id_seq', 302, true);


--
-- Name: bewerbung_bewerbungs_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE bewerbung_bewerbungs_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: bewerbung_bewerbungs_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE bewerbung_bewerbungs_id_seq OWNED BY a23_request.request_id;


--
-- Name: bewerbung_bewerbungs_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('bewerbung_bewerbungs_id_seq', 7, true);


--
-- Name: branchen_kat_branchen_kat_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE branchen_kat_branchen_kat_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: branchen_kat_branchen_kat_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE branchen_kat_branchen_kat_id_seq OWNED BY a23_industry.industry_id;


--
-- Name: branchen_kat_branchen_kat_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('branchen_kat_branchen_kat_id_seq', 240, true);


--
-- Name: common_container_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE common_container_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: common_container_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE common_container_id_seq OWNED BY a23_common_container.common_container_id;


--
-- Name: common_container_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('common_container_id_seq', 27, true);


--
-- Name: einschraenkung_merkmal_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE einschraenkung_merkmal_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: einschraenkung_merkmal_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE einschraenkung_merkmal_id_seq OWNED BY a23_handicap.handicap_id;


--
-- Name: einschraenkung_merkmal_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('einschraenkung_merkmal_id_seq', 43, true);


--
-- Name: einschraenkung_mitglied_einschraenkung_mitglied_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE einschraenkung_mitglied_einschraenkung_mitglied_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: einschraenkung_mitglied_einschraenkung_mitglied_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE einschraenkung_mitglied_einschraenkung_mitglied_id_seq OWNED BY a23_seeker_link_to_handicap.seeker_handicap_id;


--
-- Name: einschraenkung_mitglied_einschraenkung_mitglied_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('einschraenkung_mitglied_einschraenkung_mitglied_id_seq', 10, true);


--
-- Name: einschraenkung_stellen_einschraenkung_stellen_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE einschraenkung_stellen_einschraenkung_stellen_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: einschraenkung_stellen_einschraenkung_stellen_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE einschraenkung_stellen_einschraenkung_stellen_id_seq OWNED BY a23_offer_link_to_handicap.offer_handicap_id;


--
-- Name: einschraenkung_stellen_einschraenkung_stellen_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('einschraenkung_stellen_einschraenkung_stellen_id_seq', 15, true);


--
-- Name: email_email_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE email_email_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: email_email_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE email_email_id_seq OWNED BY a23_provider_member_email.email_id;


--
-- Name: email_email_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('email_email_id_seq', 3, true);


--
-- Name: filestore_container_filestore_container_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE filestore_container_filestore_container_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: filestore_container_filestore_container_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE filestore_container_filestore_container_id_seq OWNED BY a23_filestore_container.filestore_container_id;


--
-- Name: filestore_container_filestore_container_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('filestore_container_filestore_container_id_seq', 2, true);


--
-- Name: filestore_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE filestore_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: filestore_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE filestore_id_seq OWNED BY a23_filestore.file_id;


--
-- Name: filestore_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('filestore_id_seq', 11, true);


--
-- Name: firma_firmen_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE firma_firmen_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: firma_firmen_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE firma_firmen_id_seq OWNED BY a23_provider.provider_id;


--
-- Name: firma_firmen_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('firma_firmen_id_seq', 9, true);


--
-- Name: firmen_black_list_firmen_black_list_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE firmen_black_list_firmen_black_list_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: firmen_black_list_firmen_black_list_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE firmen_black_list_firmen_black_list_id_seq OWNED BY a23_provider_black_list.provider_black_list_id;


--
-- Name: firmen_black_list_firmen_black_list_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('firmen_black_list_firmen_black_list_id_seq', 1, true);


--
-- Name: firmen_mitarbeiter_mitarbeiter_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE firmen_mitarbeiter_mitarbeiter_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: firmen_mitarbeiter_mitarbeiter_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE firmen_mitarbeiter_mitarbeiter_id_seq OWNED BY a23_provider_member.member_id;


--
-- Name: firmen_mitarbeiter_mitarbeiter_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('firmen_mitarbeiter_mitarbeiter_id_seq', 1, false);


--
-- Name: firmen_mitarbeiter_tel_nr_firmen_mitarbeiter_tel_nr_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE firmen_mitarbeiter_tel_nr_firmen_mitarbeiter_tel_nr_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: firmen_mitarbeiter_tel_nr_firmen_mitarbeiter_tel_nr_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE firmen_mitarbeiter_tel_nr_firmen_mitarbeiter_tel_nr_id_seq OWNED BY a23_provider_member_phone.phone_id;


--
-- Name: firmen_mitarbeiter_tel_nr_firmen_mitarbeiter_tel_nr_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('firmen_mitarbeiter_tel_nr_firmen_mitarbeiter_tel_nr_id_seq', 1, false);


--
-- Name: game_funk; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE game_funk (
    nachrichten_id integer NOT NULL,
    nachrichten_text text NOT NULL
);


--
-- Name: game_funk_nachrichten_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE game_funk_nachrichten_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: game_funk_nachrichten_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE game_funk_nachrichten_id_seq OWNED BY game_funk.nachrichten_id;


--
-- Name: game_funk_nachrichten_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('game_funk_nachrichten_id_seq', 1, true);


--
-- Name: game_landkarte; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE game_landkarte (
    objekt_name text,
    geo_data polygon NOT NULL,
    spiel_name text NOT NULL
);


--
-- Name: game_spieler; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE game_spieler (
    mitglieds_id integer NOT NULL,
    "position" point NOT NULL,
    proviant integer NOT NULL,
    zustand integer NOT NULL,
    segelflaeche integer NOT NULL,
    segelstellung integer NOT NULL,
    kurs double precision NOT NULL,
    spielzug_abgeschlossen integer NOT NULL,
    geplanter_route path
);


--
-- Name: game_werte; Type: TABLE; Schema: public; Owner: -; Tablespace:
--

CREATE TABLE game_werte (
    bezeichner text,
    text_wert text NOT NULL,
    int_wert integer NOT NULL
);


--
-- Name: global_conf_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE global_conf_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: global_conf_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE global_conf_id_seq OWNED BY a23_global_conf.conf_id;


--
-- Name: global_conf_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('global_conf_id_seq', 11, true);


--
-- Name: mitglied_mitglieds_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE mitglied_mitglieds_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: mitglied_mitglieds_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE mitglied_mitglieds_id_seq OWNED BY a23_seeker.seeker_id;


--
-- Name: mitglied_mitglieds_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('mitglied_mitglieds_id_seq', 10, true);


--
-- Name: mitgliederberufe_mitgliederberufe_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE mitgliederberufe_mitgliederberufe_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: mitgliederberufe_mitgliederberufe_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE mitgliederberufe_mitgliederberufe_id_seq OWNED BY a23_seeker_link_to_stuff.seeker_stuff_id;


--
-- Name: mitgliederberufe_mitgliederberufe_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('mitgliederberufe_mitgliederberufe_id_seq', 19, true);


--
-- Name: mitglieds_tel_nr_mitglieds_tel_nr_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE mitglieds_tel_nr_mitglieds_tel_nr_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: mitglieds_tel_nr_mitglieds_tel_nr_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE mitglieds_tel_nr_mitglieds_tel_nr_id_seq OWNED BY a23_seeker_phone.phone_id;


--
-- Name: mitglieds_tel_nr_mitglieds_tel_nr_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('mitglieds_tel_nr_mitglieds_tel_nr_id_seq', 49, true);


--
-- Name: qualitaeten_merkmal_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE qualitaeten_merkmal_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: qualitaeten_merkmal_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE qualitaeten_merkmal_id_seq OWNED BY a23_quality.quality_id;


--
-- Name: qualitaeten_merkmal_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('qualitaeten_merkmal_id_seq', 175, true);


--
-- Name: qualitaeten_mitglied_qualitaeten_mitglied_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE qualitaeten_mitglied_qualitaeten_mitglied_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: qualitaeten_mitglied_qualitaeten_mitglied_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE qualitaeten_mitglied_qualitaeten_mitglied_id_seq OWNED BY a23_seeker_link_to_quality.seeker_quality_id;


--
-- Name: qualitaeten_mitglied_qualitaeten_mitglied_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('qualitaeten_mitglied_qualitaeten_mitglied_id_seq', 71, true);


--
-- Name: qualitaeten_stelle_qualitaeten_stelle_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE qualitaeten_stelle_qualitaeten_stelle_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: qualitaeten_stelle_qualitaeten_stelle_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE qualitaeten_stelle_qualitaeten_stelle_id_seq OWNED BY a23_offer_link_to_quality.offer_quality_id;


--
-- Name: qualitaeten_stelle_qualitaeten_stelle_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('qualitaeten_stelle_qualitaeten_stelle_id_seq', 52, true);


--
-- Name: stelle_stellen_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE stelle_stellen_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: stelle_stellen_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE stelle_stellen_id_seq OWNED BY a23_offer.offer_id;


--
-- Name: stelle_stellen_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('stelle_stellen_id_seq', 9, true);


--
-- Name: stellen_berufe_stellen_berufe_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE stellen_berufe_stellen_berufe_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- Name: stellen_berufe_stellen_berufe_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE stellen_berufe_stellen_berufe_id_seq OWNED BY a23_offer_link_to_stuff.offer_stuff_id;


--
-- Name: stellen_berufe_stellen_berufe_id_seq; Type: SEQUENCE SET; Schema: public; Owner: -
--

SELECT pg_catalog.setval('stellen_berufe_stellen_berufe_id_seq', 12, true);


--
-- Name: activity_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_activity ALTER COLUMN activity_id SET DEFAULT nextval('activity_id_seq'::regclass);


--
-- Name: activity_activity_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_activity_activity ALTER COLUMN activity_activity_id SET DEFAULT nextval('activity_activity_activity_activity_id_seq'::regclass);


--
-- Name: activity_container_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_activity_container ALTER COLUMN activity_container_id SET DEFAULT nextval('activity_container_activity_container_id_seq'::regclass);


--
-- Name: activity_filestore_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_activity_filestore ALTER COLUMN activity_filestore_id SET DEFAULT nextval('activity_filestore_activity_filestore_id_seq'::regclass);


--
-- Name: log_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_activity_logbook ALTER COLUMN log_id SET DEFAULT nextval('activity_logbook_id_seq'::regclass);


--
-- Name: link_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_activity_provider ALTER COLUMN link_id SET DEFAULT nextval('activity_firma_activity_firma_id_seq'::regclass);


--
-- Name: link_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_activity_seeker ALTER COLUMN link_id SET DEFAULT nextval('activity_mitglied_activity_mitglied_id_seq'::regclass);


--
-- Name: common_container_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_common_container ALTER COLUMN common_container_id SET DEFAULT nextval('common_container_id_seq'::regclass);


--
-- Name: a23_file_reserve_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_file_reserve ALTER COLUMN a23_file_reserve_id SET DEFAULT nextval('a23_file_reserve_a23_file_reserve_id_seq'::regclass);


--
-- Name: file_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_filestore ALTER COLUMN file_id SET DEFAULT nextval('filestore_id_seq'::regclass);


--
-- Name: filestore_container_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_filestore_container ALTER COLUMN filestore_container_id SET DEFAULT nextval('filestore_container_filestore_container_id_seq'::regclass);


--
-- Name: conf_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_global_conf ALTER COLUMN conf_id SET DEFAULT nextval('global_conf_id_seq'::regclass);


--
-- Name: handicap_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_handicap ALTER COLUMN handicap_id SET DEFAULT nextval('einschraenkung_merkmal_id_seq'::regclass);


--
-- Name: industry_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_industry ALTER COLUMN industry_id SET DEFAULT nextval('branchen_kat_branchen_kat_id_seq'::regclass);


--
-- Name: newsletter_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_newsletter_log ALTER COLUMN newsletter_id SET DEFAULT nextval('a23_newsletter_log_newsletter_id_seq'::regclass);


--
-- Name: a23_newsletter_sent_to_seeker_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_newsletter_sent_to_seeker ALTER COLUMN a23_newsletter_sent_to_seeker_id SET DEFAULT nextval('a23_newsletter_sent_to_seeker_a23_newsletter_sent_to_seeker_seq'::regclass);


--
-- Name: offer_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_offer ALTER COLUMN offer_id SET DEFAULT nextval('stelle_stellen_id_seq'::regclass);


--
-- Name: offer_handicap_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_offer_link_to_handicap ALTER COLUMN offer_handicap_id SET DEFAULT nextval('einschraenkung_stellen_einschraenkung_stellen_id_seq'::regclass);


--
-- Name: offer_quality_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_offer_link_to_quality ALTER COLUMN offer_quality_id SET DEFAULT nextval('qualitaeten_stelle_qualitaeten_stelle_id_seq'::regclass);


--
-- Name: offer_stuff_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_offer_link_to_stuff ALTER COLUMN offer_stuff_id SET DEFAULT nextval('stellen_berufe_stellen_berufe_id_seq'::regclass);


--
-- Name: provider_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_provider ALTER COLUMN provider_id SET DEFAULT nextval('firma_firmen_id_seq'::regclass);


--
-- Name: provider_black_list_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_provider_black_list ALTER COLUMN provider_black_list_id SET DEFAULT nextval('firmen_black_list_firmen_black_list_id_seq'::regclass);


--
-- Name: link_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_provider_filestore ALTER COLUMN link_id SET DEFAULT nextval('a23_provider_filestore_link_id_seq'::regclass);


--
-- Name: member_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_provider_member ALTER COLUMN member_id SET DEFAULT nextval('firmen_mitarbeiter_mitarbeiter_id_seq'::regclass);


--
-- Name: email_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_provider_member_email ALTER COLUMN email_id SET DEFAULT nextval('email_email_id_seq'::regclass);


--
-- Name: phone_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_provider_member_phone ALTER COLUMN phone_id SET DEFAULT nextval('firmen_mitarbeiter_tel_nr_firmen_mitarbeiter_tel_nr_id_seq'::regclass);


--
-- Name: provider_phone_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_provider_phone ALTER COLUMN provider_phone_id SET DEFAULT nextval('a23_provider_phone_provider_phone_id_seq'::regclass);


--
-- Name: quality_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_quality ALTER COLUMN quality_id SET DEFAULT nextval('qualitaeten_merkmal_id_seq'::regclass);


--
-- Name: request_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_request ALTER COLUMN request_id SET DEFAULT nextval('bewerbung_bewerbungs_id_seq'::regclass);


--
-- Name: seeker_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_seeker ALTER COLUMN seeker_id SET DEFAULT nextval('mitglied_mitglieds_id_seq'::regclass);


--
-- Name: link_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_seeker_filestore ALTER COLUMN link_id SET DEFAULT nextval('a23_seeker_filestore_link_id_seq'::regclass);


--
-- Name: seeker_handicap_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_seeker_link_to_handicap ALTER COLUMN seeker_handicap_id SET DEFAULT nextval('einschraenkung_mitglied_einschraenkung_mitglied_id_seq'::regclass);


--
-- Name: seeker_quality_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_seeker_link_to_quality ALTER COLUMN seeker_quality_id SET DEFAULT nextval('qualitaeten_mitglied_qualitaeten_mitglied_id_seq'::regclass);


--
-- Name: seeker_stuff_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_seeker_link_to_stuff ALTER COLUMN seeker_stuff_id SET DEFAULT nextval('mitgliederberufe_mitgliederberufe_id_seq'::regclass);


--
-- Name: log_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_seeker_logbook ALTER COLUMN log_id SET DEFAULT nextval('a23_seeker_logbook_id_seq'::regclass);


--
-- Name: phone_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_seeker_phone ALTER COLUMN phone_id SET DEFAULT nextval('mitglieds_tel_nr_mitglieds_tel_nr_id_seq'::regclass);


--
-- Name: stuff_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_stuff_type ALTER COLUMN stuff_id SET DEFAULT nextval('beruf_berufs_id_seq'::regclass);


--
-- Name: a23_version_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE a23_version ALTER COLUMN a23_version_id SET DEFAULT nextval('a23_version_a23_version_id_seq'::regclass);


--
-- Name: nachrichten_id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE game_funk ALTER COLUMN nachrichten_id SET DEFAULT nextval('game_funk_nachrichten_id_seq'::regclass);


--
-- Data for Name: a23_activity; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_activity (activity_id, time_pressure, priority, alarm_time, snooze_interval, delete_date, title, note) VALUES (3, 55, 60, '2009-01-19 03:17:35.703', 28800, NULL, 'Anmerkungen zu Firmen nachbearbeiten', 'Es ist einiges ereignet abgelaufen. Nochmal prüfen!');
INSERT INTO a23_activity (activity_id, time_pressure, priority, alarm_time, snooze_interval, delete_date, title, note) VALUES (4, 30, 66, '2009-01-19 23:27:02.906', 86400, NULL, 'Schwarze Listen', 'Einige Neuzugänge habens nötig...');


--
-- Data for Name: a23_activity_activity; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_activity_activity (owner_id, aim_id, activity_activity_id) VALUES (4, 3, 1);


--
-- Data for Name: a23_activity_container; Type: TABLE DATA; Schema: public; Owner: -
--



--
-- Data for Name: a23_activity_filestore; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_activity_filestore (activity_id, filestore_id, activity_filestore_id) VALUES (3, 5, 1);
INSERT INTO a23_activity_filestore (activity_id, filestore_id, activity_filestore_id) VALUES (3, 4, 2);
INSERT INTO a23_activity_filestore (activity_id, filestore_id, activity_filestore_id) VALUES (4, 4, 3);


--
-- Data for Name: a23_activity_logbook; Type: TABLE DATA; Schema: public; Owner: -
--



--
-- Data for Name: a23_activity_provider; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_activity_provider (activity_id, provider_id, link_id) VALUES (4, 5, 1);


--
-- Data for Name: a23_activity_seeker; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_activity_seeker (activity_id, seeker_id, link_id) VALUES (3, 7, 1);
INSERT INTO a23_activity_seeker (activity_id, seeker_id, link_id) VALUES (4, 7, 2);


--
-- Data for Name: a23_common_container; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_common_container (common_container_id, name, catalog) VALUES (9, 'Sucher: Mustermann Benno', '[DEFAULT]');
INSERT INTO a23_common_container (common_container_id, name, catalog) VALUES (15, 'Sucher: Stütz Lisa: Bewerbungen', '[DEFAULT]');
INSERT INTO a23_common_container (common_container_id, name, catalog) VALUES (12, 'Sucher: Mustermann Benno: Bewerbungen', '[DEFAULT]');
INSERT INTO a23_common_container (common_container_id, name, catalog) VALUES (16, 'Sucher: Mustermann Benno: Passfotos', '[DEFAULT]');
INSERT INTO a23_common_container (common_container_id, name, catalog) VALUES (23, 'Sucher: Mustermann Benno: Zeugnisse', '[DEFAULT]');
INSERT INTO a23_common_container (common_container_id, name, catalog) VALUES (8, 'Sucher: Mustermann Heinz', '[DEFAULT]');
INSERT INTO a23_common_container (common_container_id, name, catalog) VALUES (13, 'Sucher: Mustermann Heinz: Bewerbungen', '[DEFAULT]');
INSERT INTO a23_common_container (common_container_id, name, catalog) VALUES (17, 'Sucher: Mustermann Heinz: Passfotos', '[DEFAULT]');
INSERT INTO a23_common_container (common_container_id, name, catalog) VALUES (22, 'Sucher: Mustermann Heinz: Zeugnisse', '[DEFAULT]');
INSERT INTO a23_common_container (common_container_id, name, catalog) VALUES (14, 'Sucher: Rank Anja: Bewerbungen', '[DEFAULT]');
INSERT INTO a23_common_container (common_container_id, name, catalog) VALUES (11, 'Sucher: Rank Anja', '[DEFAULT]');
INSERT INTO a23_common_container (common_container_id, name, catalog) VALUES (18, 'Sucher: Rank Anja: Passfotos', '[DEFAULT]');
INSERT INTO a23_common_container (common_container_id, name, catalog) VALUES (21, 'Sucher: Rank Anja: Zeugnisse', '[DEFAULT]');
INSERT INTO a23_common_container (common_container_id, name, catalog) VALUES (10, 'Sucher: Stütz Lisa', '[DEFAULT]');
INSERT INTO a23_common_container (common_container_id, name, catalog) VALUES (27, 'Sucher: Stütz Lisa: Angeschriebene Stellen', '[DEFAULT]');
INSERT INTO a23_common_container (common_container_id, name, catalog) VALUES (19, 'Sucher: Stütz Lisa: Passfotos', '[DEFAULT]');
INSERT INTO a23_common_container (common_container_id, name, catalog) VALUES (20, 'Sucher: Stütz Lisa: Zeugnisse', '[DEFAULT]');
INSERT INTO a23_common_container (common_container_id, name, catalog) VALUES (4, 'Allgemeine Unterlagen: Bilder und Fotos', '[DEFAULT]');
INSERT INTO a23_common_container (common_container_id, name, catalog) VALUES (2, 'Gemeinsame Dateien', '[DEFAULT]');
INSERT INTO a23_common_container (common_container_id, name, catalog) VALUES (3, 'Allgemeine Unterlagen: Dokumente', '[DEFAULT]');
INSERT INTO a23_common_container (common_container_id, name, catalog) VALUES (5, 'Allgemeine Unterlagen: Flyer', '[DEFAULT]');
INSERT INTO a23_common_container (common_container_id, name, catalog) VALUES (6, 'Allgemeine Unterlagen: Tipps', '[DEFAULT]');


--
-- Data for Name: a23_file_reserve; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_file_reserve (file_id, editor_id, start_date, end_date, note, a23_file_reserve_id) VALUES (4, 7, '2009-01-18 01:24:18.25', '2009-01-19 00:00:00', 'Muss ich nochmal ran', 1);
INSERT INTO a23_file_reserve (file_id, editor_id, start_date, end_date, note, a23_file_reserve_id) VALUES (5, 7, '2009-01-13 01:50:59.031', '2009-01-15 00:00:00', 'Muss noch ,mal ran.', 2);


--
-- Data for Name: a23_filestore; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_filestore (file_id, name, version_of_id, bin_data, version_tag, md5_sum, create_date, delete_date, file_summary) VALUES (4, 'logo.ico', NULL, '\\000\\000\\001\\000\\001\\00000\\000\\000\\001\\000\\030\\000\\250\\034\\000\\000\\026\\000\\000\\000(\\000\\000\\0000\\000\\000\\000`\\000\\000\\000\\001\\000\\030\\000\\000\\000\\000\\000\\200\\034\\000\\000\\000\\000\\000\\000\\000\\000\\000\\000\\000\\000\\000\\000\\000\\000\\000\\000\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\375\\372\\372\\350\\330\\330\\332\\275\\275\\266\\213\\213\\224bb\\202MMv??e,,`&&m33wAA\\206SS\\253}}\\327\\267\\267\\344\\324\\324\\373\\370\\370\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\364\\351\\351\\307\\240\\240\\230XXg\\035\\035M\\000\\000J\\000\\000J\\000\\000J\\000\\000H\\000\\000J\\000\\000E\\000\\000?\\000\\000>\\000\\000:\\000\\0004\\000\\0009\\000\\000R\\027\\027\\207TT\\272\\231\\231\\357\\345\\345\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\353\\333\\333\\264||w&&[\\002\\002Z\\000\\000^\\003\\003c\\005\\005g\\006\\006i\\010\\010j\\010\\010i\\010\\010g\\007\\007e\\006\\006b\\004\\004^\\003\\003X\\001\\001O\\000\\000J\\000\\000>\\000\\0005\\000\\0008\\001\\001W\\036\\036\\246||\\357\\336\\336\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\371\\362\\362\\304\\222\\222w\\034\\034b\\002\\002g\\006\\006o\\014\\014t\\020\\020y\\023\\023|\\025\\025~\\027\\027~\\027\\027\\200\\030\\030\\200\\030\\030~\\027\\027~\\026\\026{\\024\\024x\\022\\022t\\017\\017o\\012\\012f\\006\\006_\\003\\003V\\001\\001I\\000\\000<\\000\\0004\\000\\000M\\025\\025\\265\\214\\214\\366\\357\\357\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\351\\322\\322\\233MMn\\013\\013p\\013\\013y\\023\\023~\\027\\027\\203\\033\\033\\207\\037\\037\\212""\\214$$\\215%%\\215$$\\215%%\\215%%\\214$$\\213##\\212!!\\206\\036\\036\\205\\035\\035\\201\\032\\032}\\026\\026x\\021\\021p\\014\\014f\\006\\006Y\\002\\002L\\000\\000;\\000\\0006\\000\\000zDD\\341\\312\\312\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\325\\252\\252\\200\\036\\036t\\014\\014|\\025\\025\\203\\034\\034\\212!!\\217&&\\222**\\224,,\\223++\\224,,\\224,,\\221**\\221))\\220((\\217''''\\217''''\\217&&\\216%%\\214$$\\212""\\207  \\205\\035\\035\\201\\032\\032|\\024\\024s\\016\\016g\\006\\006Z\\001\\001E\\000\\0004\\000\\000E\\013\\013\\311\\244\\244\\376\\375\\375\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\376\\376\\320\\237\\237y\\023\\023|\\025\\025\\205\\036\\036\\214$$\\221))\\225--\\226//\\23111\\23000\\227//\\225--\\224,,\\223,,\\222**\\221))\\220((\\217''''\\215%%\\216&&\\216&&\\215%%\\212""\\212""\\210  \\205\\035\\035\\200\\031\\031z\\024\\024p\\013\\013`\\004\\004N\\000\\0009\\000\\0008\\003\\003\\274\\222\\222\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\324\\246\\246|\\024\\024\\202\\032\\032\\212""\\220((\\226..\\23111\\23233\\23233\\23222\\23111\\23011\\227//\\226..\\224,,\\224,,\\224,,\\222**\\221))\\217''''\\216&&\\215%%\\215%%\\213##\\213##\\212""\\211!!\\207\\037\\037\\205\\035\\035\\177\\027\\027u\\017\\017g\\007\\007S\\000\\000<\\000\\0001\\000\\000\\306\\240\\240\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\342\\301\\301\\205\\037\\037\\205\\034\\034\\215%%\\223++\\23000\\23233\\23344\\23344\\23344\\23233\\23100\\227/0\\226-.\\226-.\\225,,\\224++\\224*+\\223**\\223++\\221((\\217%&\\215$$\\214!"\\213!"\\213##\\213##\\213##\\212!!\\210  \\206\\036\\036\\200\\031\\031w\\021\\021h\\007\\007T\\001\\001<\\000\\000A\\016\\016\\324\\266\\266\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\356\\330\\330\\221//\\210\\037\\037\\220((\\225--\\23222\\23455\\23455\\23344\\23444\\23444\\23344\\236:8\\236<:\\235:8\\235<:\\236<9\\234;8\\234<9\\22721\\223)*\\222))\\23053\\232:7\\231:7\\22531\\214#$\\213""\\213"#\\212""\\212""\\211!!\\207\\036\\036\\201\\032\\032y\\023\\023i\\010\\010R\\000\\0008\\000\\000P\\025\\025\\353\\330\\330\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\372\\363\\363\\253YY\\207\\036\\036\\222**\\226//\\23233\\23566\\23566\\23466\\23455\\23344\\23444\\230./\\300\\201q\\322\\252\\221\\321\\247\\217\\324\\257\\225\\326\\262\\227\\326\\263\\230\\332\\272\\236\\262h[\\223))\\263m_\\324\\255\\224\\334\\277\\241\\337\\303\\245\\326\\257\\226\\270vh\\217(''\\214#$\\214$$\\213##\\213##\\213##\\207\\037\\037\\203\\034\\034y\\022\\022g\\006\\006P\\000\\0001\\000\\000|II\\372\\364\\364\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\321\\235\\235\\213!!\\222))\\227//\\23333\\23566\\23566\\23566\\23466\\23566\\23344\\23355\\23101\\264i^\\337\\306\\246\\340\\304\\246\\336\\300\\243\\330\\263\\231\\330\\264\\232\\335\\277\\242\\260cY\\255\\\\S\\341\\310\\251\\340\\310\\251\\313\\232\\204\\304\\215z\\334\\277\\243\\337\\304\\246\\256cW\\214!"\\216&&\\214$$\\212""\\213##\\213""\\210  \\202\\031\\031w\\020\\020c\\004\\004G\\000\\0002\\000\\000\\277\\232\\232\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\365\\344\\344\\23277\\221))\\227//\\23344\\23455\\23577\\23577\\23577\\23577\\23577\\23466\\23466\\23445\\23487\\306\\222~\\337\\304\\246\\334\\300\\243\\300\\203r\\237<:\\234:8\\23022\\254XQ\\275\\201p\\275\\177o\\23285\\221''(\\314\\237\\210\\343\\313\\254\\313\\233\\205\\215!#\\220((\\216&&\\214$$\\214$$\\214$$\\213##\\207\\037\\037\\202\\031\\031r\\015\\015\\\\\\002\\002>\\000\\000L\\026\\026\\360\\340\\340\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\315\\222\\222\\223))\\23111\\23344\\23455\\23477\\23577\\23588\\23688\\23588\\23577\\23577\\23577\\23677\\23334\\240?<\\310\\222\\200\\340\\307\\250\\335\\301\\243\\305\\216|\\237<:\\226-.\\226..\\223)*\\225--\\240E@\\255^T\\325\\262\\227\\337\\305\\246\\303\\215y\\217"$\\221))\\220((\\217&&\\216&&\\214$$\\214$$\\213##\\210  }\\026\\026k\\011\\011T\\001\\0016\\000\\000\\247xx\\377\\377\\377\\377\\377\\377\\377\\377\\377\\365\\346\\346\\246FF\\23333\\23566\\23688\\23699\\23688\\23577\\23688\\23699\\23699\\23688\\236::\\23599\\236::\\23588\\23335\\23356\\275|n\\337\\302\\245\\345\\315\\256\\313\\233\\206\\235<:\\227//\\227//\\23264\\315\\235\\207\\341\\310\\251\\340\\304\\246\\322\\250\\217\\242GB\\221''(\\223++\\221))\\221))\\217''''\\216&&\\213""\\214$$\\214$$\\205\\035\\035w\\021\\021c\\004\\004E\\000\\000Q\\030\\030\\361\\343\\343\\377\\377\\377\\377\\377\\377\\336\\262\\262\\23677\\240;;\\240<<\\241==\\240;;\\237::\\236::\\237;;\\237;;\\237<<\\237<<\\237<<\\240<<\\237<<\\245IF\\246LI\\244IF\\23456\\271ui\\336\\302\\247\\342\\311\\254\\261dZ\\226,.\\227./\\23043\\264k`\\324\\255\\224\\336\\303\\245\\314\\240\\210\\23053\\223**\\223++\\222**\\222**\\221))\\221))\\216&&\\214$$\\214$$\\213""\\200\\031\\031o\\013\\013V\\001\\0017\\000\\000\\305\\243\\243\\377\\377\\377\\374\\370\\370\\305\\177\\177\\244>>\\245@@\\243??\\242??\\242??\\242>>\\240>>\\241>>\\241??\\241??\\241@@\\241??\\242@@\\236:;\\306\\215|\\330\\267\\236\\330\\263\\232\\247NJ\\255[U\\332\\272\\240\\345\\316\\260\\271rg\\252VO\\313\\234\\207\\314\\235\\211\\247NI\\260bX\\336\\302\\244\\336\\304\\245\\257`V\\222))\\225--\\225--\\222++\\221**\\222**\\221))\\217''''\\216&&\\214$$\\207\\036\\036x\\022\\022d\\005\\005A\\000\\000\\205RR\\371\\364\\364\\364\\345\\345\\265ZZ\\252GG\\251FF\\246CC\\245BB\\245CC\\244CC\\244CC\\244CC\\244DD\\243CC\\243DD\\243CC\\243DD\\241?@\\272ui\\343\\315\\257\\342\\312\\256\\325\\261\\232\\331\\265\\235\\342\\311\\254\\335\\301\\246\\253XR\\254VQ\\340\\303\\247\\343\\315\\256\\326\\261\\230\\323\\254\\223\\340\\304\\246\\335\\277\\242\\252UN\\223+,\\225..\\225--\\224,,\\223++\\222++\\222**\\220((\\220((\\216&&\\213##\\202\\032\\032o\\014\\014S\\000\\000N\\017\\017\\355\\334\\334\\353\\315\\315\\263RR\\260PP\\256MM\\253JJ\\251HH\\250GG\\246GG\\247HH\\246GG\\246GG\\245HH\\245GG\\245HH\\245HH\\244FF\\246JI\\301\\202v\\326\\257\\231\\336\\300\\247\\335\\276\\245\\326\\254\\230\\272si\\241AA\\240>?\\262e]\\317\\245\\217\\332\\274\\240\\334\\274\\242\\316\\242\\213\\263j_\\23122\\22700\\22711\\226//\\225..\\225--\\224,,\\223,,\\222**\\222**\\221((\\216&&\\211  x\\022\\022_\\004\\004F\\000\\000\\322\\261\\261\\335\\253\\253\\267YY\\265XX\\262TT\\257QQ\\255PP\\254MM\\253MM\\251KK\\251LL\\251MM\\251MM\\250MM\\250LL\\250MM\\250NN\\247JK\\246HI\\250NM\\252RP\\251RP\\247KJ\\242CD\\243DD\\242CC\\237=>\\240BA\\242EB\\242DB\\236<<\\23123\\23122\\23122\\22711\\22711\\226//\\225..\\225--\\224,,\\224++\\224,,\\222**\\221((\\215$$\\177\\027\\027j\\010\\010O\\000\\000\\255}}\\322\\222\\222\\275cc\\272^^\\265YY\\264WW\\262VV\\260UU\\257TT\\256RR\\255SS\\253SS\\254SS\\254SS\\253TT\\253TT\\252SS\\252SS\\251QQ\\250MN\\250LM\\247LM\\246JJ\\246JJ\\244HH\\243EE\\242EE\\242AA\\237==\\2359:\\23399\\23488\\23366\\23033\\23122\\23011\\22700\\226..\\225--\\224--\\224--\\224,,\\223++\\222**\\220''''\\204\\033\\033q\\015\\015U\\000\\000\\231aa\\316\\212\\212\\277ee\\275bb\\270[\\\\\\266XX\\264WW\\263WX\\262VV\\260VV\\260UU\\257TT\\256TT\\254TU\\254UU\\254TT\\254SS\\253SS\\253QQ\\252QQ\\251OO\\250MM\\247KK\\246II\\244GG\\243DD\\241BB\\241??\\237==\\236;;\\23599\\23366\\23366\\23233\\23000\\23100\\227//\\227//\\226..\\227./\\225--\\225..\\224--\\224,-\\222*+\\210  w\\022\\022_\\003\\003\\215OO\\364\\343\\343\\341\\263\\262\\345\\275\\274\\345\\276\\276\\345\\276\\276\\345\\300\\300\\345\\300\\277\\344\\277\\277\\343\\277\\277\\344\\301\\301\\343\\300\\300\\343\\277\\277\\342\\277\\276\\342\\276\\276\\343\\300\\277\\342\\276\\276\\341\\276\\276\\341\\276\\276\\342\\276\\276\\341\\276\\276\\340\\274\\273\\340\\274\\273\\337\\273\\273\\336\\270\\270\\336\\267\\267\\334\\266\\266\\334\\264\\264\\333\\263\\263\\335\\265\\265\\334\\262\\262\\332\\256\\256\\333\\257\\257\\334\\257\\257\\332\\254\\254\\331\\247\\247\\326\\243\\243\\321\\233\\233\\323\\235\\234\\324\\234\\234\\324\\237\\236\\324\\237\\235\\324\\237\\235\\326\\241\\240\\325\\240\\237\\316\\227\\226\\305\\216\\214\\275\\210\\207\\336\\304\\304\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\376\\376\\377\\376\\376\\377\\376\\376\\377\\376\\376\\377\\376\\377\\377\\376\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\376\\377\\377\\376\\377\\377\\376\\376\\377\\376\\376\\377\\376\\376\\377\\376\\376\\377\\376\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\344\\334\\366\\247\\222\\336\\251\\222\\336\\252\\226\\336\\252\\230\\335\\255\\233\\337\\256\\235\\340\\261\\241\\341\\261\\243\\341\\261\\244\\340\\261\\246\\337\\262\\247\\341\\263\\251\\341\\262\\252\\340\\262\\252\\340\\262\\252\\336\\260\\252\\335\\260\\251\\336\\260\\251\\336\\256\\251\\335\\254\\250\\333\\254\\247\\335\\252\\244\\335\\252\\243\\335\\247\\241\\332\\245\\237\\330\\241\\234\\330\\237\\231\\330\\235\\226\\327\\231\\223\\324\\224\\217\\323\\223\\214\\322\\221\\212\\323\\213\\204\\320\\206\\177\\315\\177x\\312|r\\312xo\\311rj\\306sl\\305pj\\304qj\\305pj\\303oj\\301nj\\277jh\\276jj\\275\\300\\300\\342\\235{\\344t=\\327k-\\321d\\037\\315`\\036\\312b$\\313c*\\314c.\\314d3\\313d7\\313d;\\313e>\\313eA\\312dC\\311dD\\311cD\\307`D\\306]D\\305[C\\303YA\\302U>\\302R;\\301P8\\300L5\\276F/\\274B*\\271>''\\2719"\\2704\\034\\2660\\027\\264*\\023\\262&\\017\\261%\\014\\260"\\011\\257 \\006\\256\\036\\004\\255\\033\\002\\255\\033\\001\\254\\034\\001\\255\\034\\002\\256\\032\\000\\255\\032\\000\\255\\032\\000\\254\\033\\000\\255\\025\\000\\250\\013\\000\\236\\002\\000\\221B?\\253\\254\\224\\353\\204W\\336|D\\330t4\\324t/\\323t4\\322s7\\322t<\\322vC\\323wG\\323vJ\\322wN\\323wP\\322uR\\321vU\\321vV\\321sU\\317qU\\316oT\\315kQ\\312gN\\311dL\\311`H\\307\\\\D\\305V>\\304Q:\\302M5\\277G/\\275A)\\273>%\\2728\\037\\2700\\030\\265-\\024\\264*\\022\\263''\\014\\261#\\011\\260\\037\\005\\257\\034\\003\\256\\035\\003\\256\\033\\001\\256\\030\\000\\254\\030\\000\\254\\027\\000\\254\\032\\000\\254\\025\\000\\250\\014\\000\\237\\000\\000\\220NE\\264\\311\\277\\364\\213e\\341\\203S\\333{@\\327x8\\326|?\\325\\202J\\327\\201J\\326zC\\324~M\\325\\203X\\327\\202Z\\326\\202]\\326\\203a\\326\\200]\\325\\177_\\324\\201d\\324~c\\324y]\\321w^\\320s[\\315kS\\312fO\\311bK\\310_H\\307ZC\\304S;\\301P9\\300J3\\276B*\\273;"\\2708 \\2706\\037\\2671\\032\\2650\\031\\265.\\025\\263+\\023\\263(\\020\\263!\\010\\260$\\013\\261$\\013\\261#\\013\\261%\\015\\261\\033\\001\\254\\025\\000\\250\\014\\000\\240\\000\\000\\221}u\\313\\352\\347\\373\\223v\\345\\215d\\340\\203P\\332z=\\326\\220b\\335\\315\\317\\361\\302\\272\\355\\216^\\333\\237}\\341\\315\\315\\362\\265\\247\\350\\277\\265\\353\\316\\315\\361\\222s\\333\\250\\226\\343\\317\\316\\361\\262\\246\\350\\202d\\325\\262\\251\\347\\305\\303\\355\\212x\\327iO\\312\\177n\\322\\273\\272\\350\\221\\207\\332aK\\307\\250\\244\\343\\245\\241\\341A(\\273tg\\316\\250\\250\\341\\225\\221\\334eW\\312\\254\\257\\344\\255\\260\\345\\263\\267\\351\\263\\270\\352WH\\304\\215\\212\\333\\253\\257\\346\\256\\263\\347\\266\\274\\352&\\017\\261\\021\\000\\246\\014\\000\\236\\001\\000\\223\\301\\273\\351\\371\\370\\376\\242\\220\\354\\226t\\344\\213]\\335\\203L\\331\\211S\\332\\302\\274\\356\\326\\337\\363\\317\\315\\362\\316\\315\\362\\334\\343\\365\\264\\241\\350\\311\\303\\357\\335\\342\\366\\251\\220\\344\\324\\323\\363\\341\\347\\370\\255\\233\\343\\214n\\330\\307\\304\\356\\343\\353\\372\\233\\212\\336oT\\315\\215|\\330\\335\\345\\367\\246\\240\\342hR\\312\\306\\312\\356\\311\\315\\357`K\\307\\257\\256\\346\\332\\345\\367\\202y\\325hY\\313\\317\\331\\364\\264\\267\\352\\211\\205\\330\\177{\\323O>\\301\\245\\250\\343\\304\\315\\360\\233\\234\\336\\220\\216\\333!\\012\\256\\021\\000\\246\\011\\000\\234\\030\\023\\237\\341\\333\\366\\376\\376\\377\\303\\274\\364\\235\\204\\350\\224m\\342\\214[\\335\\205O\\332\\263\\240\\350\\325\\336\\363\\317\\321\\361\\326\\333\\364\\326\\331\\364\\255\\215\\345\\313\\301\\357\\337\\343\\366\\322\\313\\362\\345\\352\\370\\317\\310\\360\\242\\206\\340\\234\\201\\336\\313\\306\\356\\341\\347\\366\\240\\217\\337y\\\\\\322\\221\\177\\331\\332\\341\\366\\250\\241\\343kU\\313\\277\\301\\353\\316\\325\\361\\273\\276\\352\\306\\313\\357\\304\\312\\360S>\\302th\\320\\314\\325\\361\\233\\231\\337cU\\310SD\\3031\\034\\266\\247\\253\\343\\261\\266\\347''\\016\\262\\035\\004\\256\\030\\000\\253\\022\\000\\245\\006\\000\\233OB\\273\\363\\360\\373\\377\\377\\377\\346\\345\\373\\244\\224\\353\\235\\177\\347\\224j\\341\\216]\\335\\243\\201\\343\\326\\333\\364\\276\\260\\353\\321\\317\\362\\323\\316\\363\\260\\214\\346\\324\\313\\362\\346\\352\\371\\347\\354\\370\\350\\354\\371\\331\\325\\364\\263\\234\\346\\250\\216\\342\\321\\314\\360\\345\\352\\370\\247\\225\\342\\201c\\324\\226\\203\\333\\332\\340\\364\\252\\241\\343pW\\314\\302\\304\\354\\320\\327\\362\\317\\325\\362\\323\\333\\366\\234\\230\\3367\\031\\270{p\\322\\307\\317\\357\\307\\320\\360\\317\\331\\366\\266\\272\\353;''\\272\\246\\250\\345\\264\\271\\352"\\010\\260\\030\\000\\254\\027\\000\\252\\021\\000\\244\\006\\000\\233\\227\\205\\331\\377\\377\\377\\377\\377\\377\\372\\372\\376\\270\\261\\362\\247\\223\\353\\234z\\345\\226j\\340\\225h\\337\\315\\312\\361\\330\\332\\365\\337\\344\\367\\320\\305\\362\\267\\225\\351\\333\\325\\365\\350\\354\\371\\324\\306\\361\\341\\336\\365\\354\\357\\371\\314\\274\\357\\266\\234\\347\\326\\321\\363\\346\\353\\370\\256\\233\\345\\212k\\327\\235\\211\\336\\333\\341\\365\\254\\243\\343uZ\\320\\304\\306\\355\\316\\323\\363\\316\\325\\363\\317\\326\\361\\206z\\3272\\021\\265}q\\322\\321\\332\\364\\204{\\326D-\\275;#\\2713\\032\\266\\252\\255\\345\\262\\267\\350$\\013\\261\\031\\000\\254\\026\\000\\251\\015\\000\\241$\\033\\252\\345\\342\\367\\377\\377\\377\\377\\377\\377\\377\\377\\377\\336\\336\\372\\257\\246\\357\\247\\217\\352\\236z\\344\\231n\\341\\302\\263\\356\\342\\353\\367\\341\\346\\367\\312\\267\\357\\300\\242\\353\\342\\336\\367\\355\\361\\372\\345\\340\\370\\352\\351\\371\\355\\357\\371\\333\\322\\364\\333\\324\\364\\344\\345\\370\\350\\354\\372\\324\\320\\363\\277\\265\\353\\256\\235\\345\\333\\342\\366\\260\\246\\345z]\\323\\312\\314\\361\\271\\266\\351\\230\\215\\335\\321\\330\\363\\272\\275\\352W?\\304}p\\324\\320\\331\\363\\254\\256\\347\\224\\220\\333\\203{\\324F0\\275\\276\\305\\355\\274\\303\\356%\\013\\260\\030\\000\\253\\025\\000\\250\\010\\000\\237\\216\\204\\327\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\372\\372\\376\\274\\274\\364\\261\\244\\356\\247\\214\\350\\241|\\344\\256\\217\\347\\316\\304\\362\\322\\310\\363\\307\\257\\356\\313\\262\\356\\342\\333\\366\\353\\351\\371\\354\\353\\371\\355\\354\\372\\344\\334\\367\\336\\323\\364\\355\\360\\372\\350\\351\\371\\341\\342\\365\\341\\344\\367\\331\\332\\365\\265\\245\\350\\324\\325\\364\\256\\242\\346|^\\323\\300\\277\\353\\261\\253\\347bB\\312\\257\\253\\347\\314\\323\\362\\230\\221\\335r`\\316\\243\\243\\340\\251\\251\\345\\252\\252\\344\\234\\234\\340E,\\276\\201x\\325zr\\320#\\007\\260\\031\\000\\254\\020\\000\\245''\\033\\255\\346\\341\\367\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\346\\351\\374\\267\\266\\363\\263\\244\\357\\255\\221\\352\\256\\214\\347\\264\\225\\350\\276\\243\\353\\312\\263\\357\\323\\301\\362\\334\\315\\365\\342\\324\\367\\345\\331\\367\\345\\330\\366\\340\\321\\365\\331\\307\\363\\322\\275\\361\\312\\264\\356\\277\\245\\351\\262\\226\\347\\245\\206\\341\\231v\\336\\215k\\332\\202^\\326wR\\323rM\\317jF\\315^9\\311Y6\\307T1\\305N,\\302B \\275<\\031\\2727\\026\\2703\\021\\266/\\015\\265)\\007\\263#\\003\\262 \\000\\257\\037\\002\\256\\032\\000\\254\\015\\000\\243\\232\\214\\335\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\375\\376\\377\\323\\326\\371\\273\\270\\363\\270\\247\\357\\266\\235\\354\\273\\240\\353\\304\\254\\356\\320\\274\\361\\332\\313\\365\\343\\330\\367\\352\\337\\371\\355\\344\\371\\354\\343\\371\\347\\333\\367\\336\\317\\365\\325\\300\\362\\314\\264\\357\\301\\245\\353\\265\\225\\350\\246\\204\\342\\233u\\337\\216g\\332\\204[\\327zR\\324qH\\320kA\\315c;\\313\\\\3\\310S*\\305K$\\301D\\035\\277=\\027\\2747\\023\\2712\\016\\267.\\012\\264*\\007\\262(\\005\\263%\\002\\262 \\002\\260\\022\\000\\250dX\\311\\370\\367\\375\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\370\\371\\376\\312\\321\\370\\302\\276\\364\\277\\256\\360\\301\\253\\356\\311\\263\\360\\324\\302\\362\\337\\321\\366\\347\\335\\370\\356\\347\\372\\360\\351\\372\\356\\347\\372\\351\\336\\370\\337\\320\\366\\326\\302\\362\\315\\266\\360\\303\\246\\355\\267\\225\\350\\252\\205\\344\\235v\\340\\221g\\334\\207[\\330~Q\\325uI\\322nB\\317g:\\314_2\\312X,\\307P%\\305G\\036\\300@\\030\\275;\\024\\2735\\017\\2720\\013\\267,\\007\\265+\\006\\264(\\003\\262\\036\\000\\2575\\035\\267\\343\\340\\370\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\364\\366\\376\\310\\320\\370\\307\\302\\364\\310\\271\\361\\314\\272\\361\\326\\306\\363\\340\\323\\366\\350\\336\\370\\355\\346\\372\\356\\350\\372\\354\\345\\372\\346\\333\\370\\335\\316\\364\\325\\301\\362\\314\\264\\357\\301\\245\\354\\266\\223\\350\\253\\203\\344\\237s\\340\\223d\\334\\212Z\\331\\200P\\327yH\\323qA\\320i:\\315a2\\313[+\\311T%\\306L\\035\\303C\\027\\300>\\023\\2758\\016\\2723\\013\\2710\\007\\267-\\004\\266(\\001\\263,\\021\\265\\320\\312\\361\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\357\\362\\375\\310\\317\\370\\314\\310\\366\\317\\302\\364\\325\\306\\364\\335\\317\\365\\345\\332\\367\\351\\340\\370\\351\\337\\370\\347\\334\\370\\341\\323\\365\\331\\311\\363\\322\\275\\361\\311\\261\\357\\276\\241\\353\\263\\220\\347\\250\\177\\344\\236o\\340\\223a\\335\\212V\\332\\201M\\327zF\\324s?\\322l8\\317d0\\315\\\\*\\312U#\\310N\\034\\304G\\026\\301B\\022\\300<\\015\\2758\\012\\2744\\006\\2720\\004\\270#\\000\\263\\261\\243\\350\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\357\\362\\375\\313\\323\\370\\320\\316\\367\\325\\314\\366\\332\\316\\366\\337\\322\\366\\342\\325\\367\\341\\324\\366\\337\\321\\366\\332\\311\\363\\323\\300\\362\\314\\265\\360\\304\\252\\355\\272\\233\\352\\256\\212\\347\\244z\\343\\232k\\337\\222^\\336\\213S\\332\\203K\\327|D\\324u=\\323n6\\320f/\\316_(\\313X!\\310Q\\032\\306K\\025\\304G\\021\\302D\\015\\301A\\011\\300;\\005\\2761\\003\\272\\253\\224\\344\\376\\376\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\361\\365\\376\\321\\333\\371\\323\\324\\371\\330\\323\\367\\331\\320\\366\\332\\315\\365\\331\\312\\364\\326\\306\\364\\322\\277\\361\\314\\266\\360\\305\\254\\356\\275\\241\\353\\264\\223\\350\\251\\203\\345\\241u\\342\\230h\\337\\220\\\\\\335\\211S\\333\\204J\\330~A\\325w:\\323o3\\321h+\\316c&\\315\\\\\\037\\312V\\030\\310R\\023\\307P\\020\\306M\\013\\306D\\004\\303F\\012\\303\\271\\241\\351\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\372\\373\\376\\342\\350\\375\\322\\330\\371\\327\\325\\370\\327\\316\\366\\325\\310\\365\\320\\300\\363\\314\\270\\360\\305\\256\\357\\277\\244\\355\\267\\231\\352\\255\\213\\347\\244}\\344\\235r\\341\\226g\\337\\217]\\335\\211S\\332\\204K\\330\\177B\\327z:\\325t3\\323o,\\322i%\\320e\\037\\316a\\031\\315]\\024\\314Z\\016\\312P\\003\\307q:\\323\\344\\332\\367\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\376\\376\\377\\360\\364\\375\\327\\337\\372\\321\\325\\370\\322\\320\\367\\316\\305\\364\\311\\272\\362\\303\\257\\357\\275\\244\\355\\263\\227\\352\\253\\212\\347\\243}\\344\\234s\\342\\227k\\340\\222d\\337\\215\\\\\\335\\211U\\333\\204N\\332\\177G\\330|B\\330z>\\327v:\\326s6\\326n/\\323f#\\321h&\\321\\275\\241\\353\\371\\367\\375\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\374\\375\\377\\352\\357\\375\\325\\336\\373\\311\\320\\370\\307\\310\\366\\305\\276\\364\\277\\262\\360\\270\\246\\356\\261\\232\\354\\253\\217\\351\\244\\205\\347\\237~\\345\\233w\\344\\230p\\342\\223k\\341\\220f\\337\\214`\\337\\211^\\337\\206Z\\336\\201T\\335yI\\332\\211]\\336\\274\\242\\353\\366\\362\\374\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\374\\375\\377\\360\\364\\376\\336\\345\\373\\310\\322\\371\\300\\305\\367\\276\\276\\364\\273\\267\\363\\267\\257\\361\\263\\247\\360\\257\\241\\356\\253\\231\\354\\247\\223\\352\\243\\215\\352\\235\\205\\350\\231\\200\\347\\223x\\346\\225y\\346\\264\\236\\354\\336\\325\\366\\370\\366\\375\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\376\\376\\377\\373\\374\\377\\365\\367\\376\\344\\351\\374\\323\\332\\372\\311\\314\\370\\300\\304\\367\\274\\273\\365\\271\\265\\363\\266\\262\\362\\273\\263\\362\\300\\271\\362\\320\\313\\366\\351\\345\\372\\370\\366\\376\\375\\375\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377\\000\\000\\000\\000\\000\\000\\377\\377', '1', '7dcb713593eeea90d02ef4eae1e85b30', '2009-01-14 22:01:57.609', NULL, 'Vorabversion des Icons');
INSERT INTO a23_filestore (file_id, name, version_of_id, bin_data, version_tag, md5_sum, create_date, delete_date, file_summary) VALUES (5, 'logo_kl.png', NULL, '\\211PNG\\015\\012\\032\\012\\000\\000\\000\\015IHDR\\000\\000\\000T\\000\\000\\000T\\010\\006\\000\\000\\000\\034k\\020\\301\\000\\000\\000\\011pHYs\\000\\000\\013\\023\\000\\000\\013\\023\\001\\000\\232\\234\\030\\000\\000\\000\\004gAMA\\000\\000\\261\\216|\\373Q\\223\\000\\000\\000 cHRM\\000\\000z%\\000\\000\\200\\203\\000\\000\\371\\377\\000\\000\\200\\351\\000\\000u0\\000\\000\\352`\\000\\000:\\230\\000\\000\\027o\\222_\\305F\\000\\000%\\263IDATx\\332b<r\\370\\360C\\016NN~FFF\\206\\177\\377\\3761\\374\\377\\377\\037\\216A\\000F\\323\\022\\200\\354&F\\014\\006p\\271\\211\\036neff\\206\\333\\005\\302\\177\\376\\374\\201\\273\\367\\367\\357\\337\\037\\001\\002\\210\\005\\030\\230\\302\\242\\242\\242\\334\\354\\354\\354tu\\0309\\201L\\357\\300#\\006\\300\\334\\001r\\355\\257_\\277X\\000\\002\\210\\205\\211\\211\\351\\017\\007\\007\\007\\003777\\303(\\240\\014\\374\\374\\371\\363\\017@\\00011 \\3054\\241T1\\012\\360\\347(\\020\\006\\010 \\246\\177H\\345\\345(\\240\\034\\000\\004\\020\\023\\250"\\032l\\345\\322P\\006\\000\\001\\304Bn\\2450P\\225\\321`\\251\\234p\\331\\013\\020@,\\204\\034E\\253\\200\\305f.r\\223\\015\\335M\\360\\332\\024\\250\\017\\304\\206\\351\\207\\225]\\364J\\000\\204"\\020 \\000\\255e\\220\\002 \\014\\003\\301Qs\\264\\250\\377\\177\\245h\\255\\325\\206\\030\\024\\317z\\351=\\204aY\\222\\221\\2570k\\000\\277\\273\\236\\340\\334}\\213bi\\305\\266\\031["\\304L\\253\\031\\366\\023\\315\\012\\305\\347\\360\\323\\344\\250\\207y\\007\\304\\177\\251[I3\\005l\\034\\220\\320\\323\\211\\334\\216X\\213\\371\\257\\233_\\002\\210\\205\\330\\332\\213R\\307\\241\\006\\342\\177H\\000~|\\015\\014<`\\000~\\377\\001ls\\374f`\\004\\206\\035\\343\\337\\177\\014\\377~\\375e\\370\\367\\033\\030\\320@6\\303\\037\\010\\373\\337\\257?`6\\343\\037 \\033\\030\\320\\014\\177\\377B\\324\\201\\002\\231\\223\\235\\201Q\\204\\237\\201AA\\222\\201UY\\206\\201\\025\\330\\246f\\201\\0060\\260YH\\365\\200\\305\\007\\000\\002\\210\\346\\001\\212\\022\\220\\277~0\\374\\373\\360\\206\\201\\341\\333''\\006\\306o\\337\\200\\001\\004\\024\\007\\005\\326\\017P\\340\\000\\003\\020\\230\\032\\377\\203\\002\\351\\347\\037 \\373\\0170 \\201|d\\014\\017`\\240\\306\\277\\377!\\374\\277 \\271/\\014\\177o\\275d\\370\\177\\360\\006\\303/~N\\006FU)\\006f#U\\006\\016y\\011\\006666\\224\\300\\245F\\356\\302\\027\\250\\000\\001\\304B\\253\\262\\006% \\177|\\003\\006\\344k\\006F`\\252d\\372\\015\\012\\220\\377\\300\\254\\314\\014\\024\\377\\303\\360\\367\\373_p\\212\\373\\367\\37578\\020\\377\\177\\007es \\015\\022\\003\\006\\034(\\300\\377\\003\\273w\\377\\177Aih\\300\\202h\\006P\\200\\376\\377\\007\\246AE\\007(\\271\\376{\\363\\225\\341\\377\\315W\\014\\014[\\3163|Q\\020c`\\3630`\\3402Ta\\000u^XYY\\301\\201K\\215\\200\\305\\005\\000\\002\\210\\205\\246\\201\\371\\373\\027\\303\\277\\367\\257\\030\\030\\277~\\002\\226\\211@\\317\\376a\\002\\246> \\375\\343\\037\\002\\377\\004\\342o\\300\\000\\001\\006\\354_``\\376\\373\\006\\324\\003\\314\\376\\240@\\006\\245\\326\\377\\277~C\\312X`V\\377\\017\\314\\366`\\032\\304\\377\\015a3\\200\\306\\037@M\\277?\\220q\\010FP\\212\\005\\322\\340\\342\\340\\351\\035\\206\\337\\007o2|\\323\\225a\\340\\210\\263e\\340\\321U\\002\\007,,\\325\\322\\242"\\003\\010 \\026Z\\004&8U~|\\303\\360\\377\\323{\\240\\007\\201\\236\\373\\015L\\215\\277\\241\\331\\373''#\\020\\003\\331\\277\\200\\364/\\006\\21080\\007\\377\\003e\\177`\\345\\363\\017\\230\\360@)\\370?\\010\\203\\003\\016\\0228\\240\\300\\004\\027\\005\\177\\240\\305\\302/Hje\\200\\00668\\353\\203\\002\\025\\024\\320\\377 )\\030\\034!@\\361\\277[\\2572\\374\\330}\\235\\341{\\2549\\003w\\254=\\003\\267\\2700\\003''''''8`\\251]\\306\\002\\004\\020\\013MR\\345\\333g\\014\\214?\\200\\025\\315?`m\\374\\007\\021\\230\\377\\201)\\364?\\250\\026\\001\\0058#0\\33311\\0035\\002\\371L\\300\\000\\001\\246\\030\\006f`\\245\\303\\004\\302@u \\374\\017\\0309\\240\\262\\022\\024\\320\\277\\2414\\254\\254\\375\\003\\245\\177\\377\\001\\027\\015\\340\\342\\001\\234\\202\\221R\\361\\037H\\261\\000*"@\\221\\361{\\312N\\206\\357{/1|\\253\\015f\\3403Vc\\340\\341\\341\\001\\247Xj\\246V\\200\\000\\254\\230=\\012\\2000\\014\\205_\\252\\336\\322#y\\005\\317\\341I\\234\\304\\315\\321\\237\\241\\203\\012\\246\\372\\322\\202\\210\\253\\026>(4\\313\\013/\\011\\215\\373\\323\\225\\352''\\204\\241c\\211\\257\\024\\227Q\\204\\203\\232\\013\\225\\357`b%KI,(\\300D\\260\\247\\305\\373\\233\\334\\342\\350\\234\\270*\\223\\310-\\367L\\230\\013\\203\\020N\\266\\000\\266\\005\\022\\\\B\\301\\341g\\310\\206\\203(9\\305b\\016\\354m\\217\\271\\254\\260\\324\\015\\346q\\204\\367\\336\\266Dx\\376\\030\\277\\234K\\000V\\314\\030\\011@\\030\\004\\202\\020\\315+}\\214\\265\\377\\360S\\366\\0266ZZ%\\340\\035\\370\\003\\235\\311\\315\\244 \\024\\227\\0052\\031\\3772\\323\\316C\\344\\202\\274\\242l5f\\205K\\311;\\303\\322\\002K\\010$\\214$9FB\\265E\\004\\377\\0234\\372\\237\\211\\242T\\265B\\003H\\2133\\214S&H3\\225\\340\\203\\326\\222d{\\354\\355\\025\\363B\\005&#\\267S\\322\\243\\012\\034\\346{\\274\\313\\362\\365p.\\253\\334\\333.m\\236\\320-z\\320\\312/\\314\\257\\003\\353\\021\\200\\025s\\307\\001\\020\\206ah\\202\\020[w\\356\\306I\\270\\023\\023\\267B\\202\\205\\205-\\301v\\340\\002\\210J\\225\\332!\\252\\364j\\273\\237\\376\\027\\230;@\\036\\233\\354\\255,\\214\\342\\350\\204\\001\\265IiT\\034\\255\\256\\003\\004W\\030~h?\\262s\\304\\000\\371\\320\\232>@\\241\\260''\\301\\033\\300\\250\\216\\366\\347Z\\354\\244\\252}\\312\\002\\325\\325\\274\\200\\245\\240\\021\\256j\\021\\310\\204J\\025\\353a\\340Y\\343\\004t@<\\227\\025\\221qY\\314\\223\\305\\030\\326Z\\023\\324\\367\\023\\371K\\273\\005`\\275\\014n\\000\\004a(\\3326p\\360\\302\\204\\016\\342X^\\334\\311\\304\\203\\013`\\365\\367\\027\\0270\\036\\010\\034 \\244\\257\\377\\267P~\\201y\\354\\310\\272\\262c\\207\\275\\031l\\305\\\\Ml\\330XBmdp\\263a\\014\\346\\321\\244\\361\\002\\200u\\001UKO\\273\\363Lg"")nJX\\254\\265\\030\\032j\\324\\034\\362\\202\\264\\204\\311=Q\\012\\006<\\247*=\\025\\0330\\271\\276\\362\\207\\206\\373\\317u\\023\\235 \\204ef<\\2555\\326\\325\\257J}\\004 \\265\\214m\\000\\204a hH\\304 l@\\315\\000lJ\\307X4\\231\\200&\\011>\\333B\\324P\\270AA\\212\\356/\\371\\344_0\\365\\221\\336\\313\\251\\345\\240w\\345\\325\\275|\\270\\357&\\326\\214n(P\\262\\217\\331E)\\351f\\035\\246\\302\\241<0b\\240\\214\\322c\\244\\035q\\376''\\010\\014D\\232\\344)431\\306\\354\\254\\001\\363\\365\\035\\240\\204\\020G\\035\\240\\006W\\010\\263\\372^"\\326\\262\\037\\222\\226Yd[\\015$\\203\\251_\\212\\352\\026\\20033\\326\\001\\020\\204\\201(\\325\\317v\\367#\\035L\\214\\361\\007@bL\\024l\\217C\\235\\011\\271\\245\\204\\345\\321\\\\\\013m6\\214\\024\\203\\313\\333\\202\\036\\362\\012Z\\010v\\325\\301F<q( lI\\272"\\024"\\300\\375`\\033@\\354\\365\\346\\227\\302x\\225\\320#\\365\\232*,f\\340\\353\\235\\200\\231\\213\\267b\\021\\244B\\023\\026\\255\\033\\020\\023@";\\355\\374/j\\330\\326at\\3474;\\357\\275\\276\\206\\243\\315\\207\\232~\\262\\036\\001(\\263\\242\\025\\000A\\0308\\373\\324\\376\\242\\177\\015\\242\\372\\203\\242\\220`\\326y\\233\\243W\\037\\006"\\202r\\336n;\\035zo\\241\\256\\327\\014\\335Yg\\200\\211\\303\\236\\210\\343\\021\\275Pa\\331\\306\\270\\007/\\336t\\267C\\265}X`\\22211,\\255\\315\\305X\\214Y\\014j\\244k#\\201\\260\\207\\222\\227,+\\021d\\035\\201U\\246\\266&5\\310~\\322\\300\\324\\017`]*\\304\\252{\\202\\341\\330\\307I\\362\\262\\021\\324\\033\\326\\270~\\300\\365\\202\\372\\011@\\211\\271\\344\\000\\010\\302P\\360\\311\\361=\\201w3\\036\\200\\035\\2501~B\\021\\012\\264\\270t\\007e\\305\\204\\227N1\\277\\243\\236ue\\231A\\353Q@\\272\\244%\\333U''\\234\\300\\035\\024O\\220\\351\\206=\\260sB\\216<u\\337sQu(\\227\\370\\202\\006\\012Kb\\213O\\267ng\\014v\\3205\\325w\\247\\300c\\005\\336v\\220j\\211<\\011\\324\\333Y\\330q\\302\\236\\200z\\357q&\\227\\376\\253S\\257\\000b!%\\006\\300\\323\\246\\317\\2370\\374{\\367\\036\\230\\345\\201\\255\\277\\217\\300\\000\\005u\\033A3\\251\\300\\362\\217\\021X\\240\\375\\007U"\\240\\246\\017\\250\\221\\315\\002L\\265\\300l\\013\\2165P3\\212\\011\\232:\\377\\374\\2056\\302\\221\\032\\337\\240J\\342?\\244l\\003\\321p\\217\\376\\207\\310A\\002\\352\\0178+#\\007&"\\360\\376B\\003\\016\\302\\207\\326\\200\\014\\377\\241\\231\\033\\221\\222!\\301\\311\\010\\015L\\006h\\340\\202\\344\\230\\030\\330\\030\\336\\036\\330\\313\\300\\265\\302\\200\\201)\\306\\037\\336\\367''\\245<\\005\\010@\\251\\031\\343\\000\\010\\302P\\2641\\340I\\034\\034\\034\\364\\246\\3063z\\002\\243.\\002\\265\\345\\027\\214\\233\\222\\260\\2200\\360\\363\\177y\\015\\270_Q?w\\211\\272\\324\\315#P\\330\\244ffA\\365\\306\\224\\370\\266\\036\\370\\255\\227\\220\\027!]\\203X\\353f\\351v2_:{\\023T\\207^h%\\2232i\\014\\031c\\270L\\301\\035\\374\\021\\220\\3433\\\\G\\014\\221Jh\\023G\\023\\356\\021\\033x\\004\\361b]\\213\\026\\0026\\214};3U\\337\\002\\311T\\324u^\\250\\033\\007\\332\\247>\\267\\247\\212Q*\\354\\227q\\013 \\026\\222R\\347\\375{\\300@\\004fq``\\376\\376\\360\\023L\\203\\232J\\240@d\\227\\027d`\\021\\342\\005\\006&3\\303\\237w? c\\226\\300|\\312*\\312\\303\\300\\302\\317\\011\\256x@f\\200\\233#@\\367\\377\\375\\010\\354M}\\375\\301\\300\\241%\\016\\351~\\202\\212\\022`\\300\\376\\005V\\006\\240\\246\\325?`\\371\\365\\347\\371\\007\\206oW\\0362\\0108j3\\374\\005\\362_\\257;\\306\\360\\371\\302]\\006\\3618\\007\\006\\016E\\011\\206_O^3<\\350]\\305\\300\\256"\\301\\240\\220\\035\\000\\016\\264\\277@\\263\\336l9\\316\\360\\345\\316c\\006^\\033m\\006v`\\200\\200\\334\\001\\356X\\374\\371\\315\\360\\343\\375''\\206;\\355\\013\\030$=\\355\\030\\376\\362\\2623\\374\\376\\366\\235\\341\\315\\206\\203\\340\\310\\205\\266Q\\030~\\377\\371\\316\\360v\\305\\032\\006\\006\\265Bp\\200\\2020\\027\\027\\027QM)\\200\\000b!:u\\276\\177\\307\\360\\357\\361Kp\\352\\004\\007*(u~\\371\\015\\356_\\263*\\0103p\\231\\31310\\261\\260B\\232;\\267\\3370\\374~\\372\\031\\334\\017g\\003\\265G\\201\\355<PS\\210\\011i\\332\\202\\201\\003\\330\\324\\002vQ\\301\\035 p\\203\\000\\324\\\\a\\001{\\034\\334k\\0026\\360\\377s\\260B\\312P`{\\226\\231\\225\\015h>3x\\024\\205\\011(\\307\\306\\313\\311\\360\\217\\213\\003\\230\\352\\031\\031$}\\255\\030X\\371\\270\\301\\345\\373\\357\\027o\\030^m?\\312 \\352j\\306 im\\0106\\033\\024\\014?\\276\\177\\007\\347\\026\\216W\\357\\301\\255\\007\\211p\\027\\006\\036\\005)pN8\\274\\355\\010\\003\\303\\317\\377\\360\\224\\314\\304\\300\\312\\360j\\353\\026\\006\\376\\000\\037\\206\\257&\\332\\360\\021*P\\021@\\010\\000\\004\\020\\013\\361\\251\\363!xx\\355\\317\\307\\237\\014\\177@\\251\\363\\013\\260\\022\\372\\006\\031\\233\\344P\\026\\001\\247\\272\\337\\277~\\002\\213R`\\240\\360\\2611\\374\\273\\363\\013\\334`\\007\\225\\225\\340\\306<0\\205\\375~\\366\\231\\201\\221\\235\\231\\201\\031\\230j\\301\\001\\013,\\002\\276]y\\002\\366\\004\\253\\214\\000\\003\\013/\\007\\270f\\372|\\366\\016\\303\\017\\240\\307\\377|\\370\\302\\300\\314\\301\\012.wA)\\366\\367o`\\345\\007,\\016\\230Y =\\231_\\300JC,\\302\\221\\201CC\\026X#\\003s\\315\\333O\\014\\267\\333\\026\\000+\\227\\317`u\\240\\300\\002\\025)/\\200\\001\\366\\373\\375g\\260\\373\\276={\\003L\\355\\300\\336\\376\\333\\017\\014\\\\r\\022\\340HE\\024\\007\\260q\\003`=\\360\\377''\\303\\2735k\\031\\230t\\224\\3015>(PaS,\\370\\000@\\000\\261\\0203Z\\377\\007X\\343\\375y\\364\\034\\234\\305\\301\\265\\372'' \\376\\366\\007\\234\\335A)\\352\\277 \\033\\270\\334c\\376\\015LY\\\\@}B\\\\\\340\\224\\367\\367\\353O\\350p\\032$\\340\\177=}\\317\\300"\\312\\315\\300$\\304\\001n\\370\\377\\375\\371\\223\\341\\347\\3437\\014\\377~\\375f`\\026\\344`\\370\\013J\\311\\300\\000\\375v\\373)\\303\\217\\347o\\201\\346\\377b\\340P\\022\\203\\224\\257\\240\\342\\002\\324\\326\\004\\226\\235\\277\\200\\3728\\200|\\036y\\011\\006>5\\031p\\000\\375\\005\\006\\350\\227\\3637\\031~>{\\015\\255\\340 \\305\\0133;\\013\\303\\233\\243\\027\\031>\\234\\271\\0121\\007T6\\203\\212\\2267\\037\\200%\\300oHW\\030\\332X\\203\\004&#\\264\\371\\003L\\245;\\2663\\210D\\2051|\\323e'':\\225\\002\\004\\020\\0131\\251\\363/\\260"\\372\\013N\\225\\300\\024\\012\\016L\\320\\010\\373\\037p\\226f\\221\\026d`\\027\\346\\005\\217O~=\\363\\204\\201\\333R\\221\\201\\031XA\\201z5\\177\\277\\374`\\370\\363\\375\\007\\003\\313_\\036\\260c9\\214\\244 1\\014\\252\\231\\200\\236\\372\\371\\364\\035\\303\\237o\\240\\221\\251_\\340\\024\\010r\\014hx\\017\\3344\\003\\211\\001S\\324?`@\\201R\\306\\237\\277\\220\\37678\\205B\\373\\332\\240\\362\\032\\224\\002\\231A\\021\\017,\\022X\\004y\\301\\362\\220\\221\\231\\177\\340A\\017P\\273T\\263%\\023\\034\\261\\314\\300\\000\\376|\\365.\\303\\331\\274v`Y\\375\\013b.#\\264\\335\\013m\\3772"AP\\305\\366z\\351:\\006\\321\\306"\\206\\357\\300"\\0034\\206J(\\225\\002\\004 \\324\\012R\\020\\206\\201\\340&\\024\\213\\021\\257\\236<\\351\\265\\377\\177\\202>\\301\\253 E\\020\\212\\227b1M\\301\\231Y\\342M\\314)\\004\\222\\220\\311\\354\\356\\354\\262\\361o}\\223\\301\\341zW\\220\\0213G\\027\\361\\265\\310\\333v;+\\231\\321\\376my\\030m\\341\\034 \\304-\\314\\036\\200\\0061\\302#w\\220\\330\\367\\007\\277.\\275\\345\\333\\003nc\\302\\336I\\367x\\012\\206g\\314d\\366,0\\011.\\375_\\244\\034#\\263\\026\\2306\\300\\340\\231\\314f\\010Z\\301:\\331\\233\\272\\203\\245\\343^\\037\\026\\344\\234]\\363\\362\\203W\\233\\2655\\211~\\267u\\300\\3316\\303\\314\\315\\305\\257\\357\\371r\\264\\262\\264\\261\\347\\371d\\245\\037\\004(ui\\355\\266\\3735>\\002\\210`\\012\\375\\363\\012X\\346<\\005\\265;\\201\\016\\377\\364\\023\\322#\\002\\246P\\360\\274\\016\\260\\355\\311&''\\010\\016\\374\\177\\300JF\\300C\\003R\\233\\003=\\311"\\313\\307\\360\\367\\304=\\206?\\3002\\212\\005\\350aF`\\017\\352\\373\\335\\327\\014\\234\\332R\\220\\251\\012.\\026`\\231\\374\\003\\032p\\240!\\265\\337\\340\\032\\036\\244\\027\\314\\006\\246N\\030\\037\\224\\335\\300\\305\\006\\270]\\012L\\221@;@)\\226\\005X\\226\\376\\006\\232\\377\\363\\345[\\006NYq\\006\\016`\\200\\2119\\2310\\334\\275v\\007\\234\\355ac\\016\\217\\227lexu\\364<\\330\\256\\377\\337\\276C\\342\\215\\021T\\346\\377\\002\\326\\350\\240\\246\\033\\254\\361\\216Hy\\260\\200\\375\\372\\3519\\303\\357\\263\\227\\031~J\\013\\203\\003\\024\\224J\\3615\\241\\000\\002\\210\\205Pv\\377}\\37718\\213\\377\\005\\365\\327?\\377\\002\\367\\210\\376\\202\\346{\\200\\021\\305*\\313\\303\\300\\304\\317\\016v\\007\\013\\033;$E\\300\\212wn\\240\\321\\234\\214\\210&\\021\\320\\341\\237O\\336b`\\026\\346b`\\023\\343c`\\223\\344g`\\002\\226\\247?n?\\003\\227i \\314\\010\\014\\004\\360\\260\\0364@Az@Y\\363\\367\\317\\037\\300\\254\\306\\002W\\007*\\026X\\331\\331\\300M\\235\\373\\023W2p\\210\\0132\\310\\304{\\003\\373\\007\\377\\030x\\015\\325\\300\\201\\371\\353\\303''HS\\011\\350\\026~\\035\\025pm\\377\\371\\305+`\\031\\310\\302\\360\\347\\007\\260\\302\\374\\007)c9yy\\031\\324\\252\\222\\200\\305\\006\\023\\303\\327g\\257\\030\\356N[\\216\\224F\\031\\301\\255\\324\\317W\\2570\\260z\\331\\200\\003\\024\\224+\\360\\215\\233\\002\\004\\020\\376\\000\\0055C\\036\\276\\002\\017z@j\\365_\\360.&\\250M\\315m(\\003\\316Z\\240\\262\\355\\327\\305\\027\\300Z\\374\\023\\003\\263\\000\\033\\260\\375\\247\\002\\014mf\\006VI^`\\023\\207\\011l\\016\\250r\\370\\365\\366#\\303\\347S7\\031\\204\\275\\214\\301\\201\\317\\247#\\313\\360\\355\\362=p\\000\\376\\207\\016G\\203\\373,\\177~\\203\\003\\022\\024\\240L@s\\3308\\271\\030~\\377\\370\\016\\356d\\201\\307L\\201\\255\\003P1\\0032\\367\\323\\365\\273\\014_\\037\\2601HG\\270\\201;\\023\\\\\\242B\\014rQ\\236\\014\\037/\\334\\004\\266\\006X\\201E\\302\\037\\006\\001CM\\006~}5p[\\026\\324<\\373~\\357\\031\\320\\315\\377\\301\\345!\\250# \\342`\\012N<"\\300\\012\\347\\336\\264\\025()\\0254.\\366\\371\\326u\\006\\201_\\277\\301\\201\\011\\032\\335\\007\\0253\\270\\002\\024 \\000_f\\314\\2020\\014D\\341''\\022+\\2028\\270\\010\\352\\346\\357\\366\\007\\270\\370\\037\\234\\025\\024\\2128X\\273T-(\\326\\266ZL\\032\\213w\\027;\\352\\036\\022\\362r\\371\\336\\273\\344\\257\\240\\357g\\001\\033Q\\376$vZ\\252N\\216M\\3623YV\\322l4\\372m\\021\\030\\246B2[\\311\\025U\\303\\036\\224`\\000b\\020:N\\334\\023\\033\\177\\262\\021\\033\\037\\233\\020\\315A\\027\\2122\\244\\364\\366\\344/6\\177A\\007''\\224\\267\\2146m`\\222\\364{\\335-\\212c\\214x\\261\\024\\2615E)\\346h\\356\\007\\324<dbx\\374J\\305\\343\\017\\3239:\\223\\261c\\242\\247\\210u\\006\\327\\365\\326\\341\\205\\035\\237*\\274E\\325i4\\317\\237\\301\\234/H\\375\\275\\210\\303\\010\\361\\350 4\\233\\230\\210\\350\\242S]\\245\\367p\\207\\021\\255Q\\022RjA\\177\\271\\375G\\0001\\236<y\\362\\203\\234\\234\\034?h\\264\\032\\275R\\372u\\013\\030\\373\\213\\366\\203k\\367_\\037 \\215\\371\\177?\\376@\\246lA}wP\\212\\001\\217\\312C\\2467@\\3254d\\030\\216\\001\\034\\210\\340P\\000\\217c2B"\\0356P\\314\\010\\033\\234\\200.\\305\\001\\341\\177\\220\\032\\034\\\\\\236\\376\\205\\216\\266\\203g2!\\335Sd6\\250\\322\\373\\017-_\\341\\362\\320r\\030\\224\\272\\031`\\025!\\274+\\313\\000gC8\\377\\241\\245\\323\\177\\350\\374\\324_\\006\\344)+Pw\\025\\330\\352e\\000V\\263`\\374\\003\\2105\\253Z\\030x\\274\\035\\031\\004\\004\\004\\030\\204\\205\\2051zN\\240\\360\\372\\371\\363\\347G\\200\\000|\\232I\\012\\300 \\014E;\\334\\377\\224\\236\\241ta\\215\\315\\037\\224v\\343B\\020$$|\\242&O\\227\\031Z3;g\\315y\\345\\026\\273S\\320\\273\\261\\265\\351g\\272\\306\\020\\372Pfl\\350\\325E\\346\\373aq\\021<M\\374tajD,\\301\\005\\211\\032\\331\\001\\305@~\\361X\\200\\360\\271\\251O\\016\\0202\\010S\\334\\3537\\315y\\2215\\325\\273\\262\\377|8C<\\243\\2242\\322R\\214C\\330?\\034\\332\\347;`\\237L\\012\\367z-\\205>\\261\\355W\\254\\364\\025\\200OsI\\001\\020\\206\\241`(n\\275\\377\\331\\004q\\347\\015t\\2431)/4\\037A\\334uQ(I\\007\\372\\230f\\372{\\220\\256e\\267\\211\\216\\347DCo\\243\\323\\234''\\216\\001\\215\\332\\342Z\\305\\034o\\013\\015g\\201_\\222\\324$\\223\\202\\3204L\\224\\371\\261\\320%R(c.\\015d\\313\\2614\\262\\251\\372>\\367\\257\\352>Vs M\\012\\231\\244\\265\\320w\\335%\\344\\2730\\301\\352X7\\232GC\\021\\235\\320\\334\\257\\277\\247.\\000\\237\\326\\262\\003 \\010\\303@\\375\\377\\177\\365d\\214n\\321u\\355\\340`\\344\\270\\300\\245{\\320\\264\\373\\0054\\274s\\333/\\254\\314`\\327\\350\\340*L\\250\\346\\255\\217\\341\\215\\224v\\200\\212\\331\\032~\\372\\013\\250\\2574+\\251\\250g\\361:\\237Hzk\\240B\\000b\\342\\254E\\360\\2152_U\\354\\244\\255J\\310\\276\\305q\\275\\022*\\273Y1qM\\3463\\357M\\377\\271\\364\\250\\005 *:\\300>\\267\\254\\312\\000\\322\\330!_\\347\\021\\200Qk\\307\\001\\020\\204\\241\\264\\240qqsq\\361\\004\\236\\304xa\\217\\340i\\334\\2141\\210\\366\\007n\\306\\211\\215\\320R^\\373\\336\\343\\273\\313\\217\\203\\333\\226\\325\\035;5\\213S\\345\\262X\\321\\320N\\230\\211\\336\\254\\214\\220\\275\\037\\303JfH^\\377or#P\\273\\002^\\334De 9\\260\\202\\241\\314\\3100\\212\\265\\021\\022hu]\\227\\231j\\204h^\\207|\\220Ff\\0026\\255\\034\\334\\0358\\361\\311Dy\\024a;\\311\\036 9\\347\\013\\206\\024J\\205\\012^\\363i\\004;\\261p\\371<&E\\251\\013baw\\343"=\\261\\272\\353];O\\277T\\271G\\000\\341\\015Pv\\003\\025\\006\\336\\356d\\006\\206\\217\\037\\200\\015`H*bc\\370\\017\\355\\3433Ag.0\\327c\\302\\331\\214HK\\024\\030\\021\\015f\\204\\363\\031\\021\\236\\371\\017\\255\\246\\240=\\026\\344\\365\\230\\377\\376\\377\\207\\227w\\3300L/\\003\\322\\372M\\230\\370?\\2308Z\\326\\376G\\302\\300:\\023h\\311\\016t=\\024l\\320\\031W\\367\\023 \\200\\360\\006(H3\\267\\220\\000\\303?`[\\020X\\203\\301\\2239z\\340\\341\\023#v%4r!\\217\\276\\260\\365?z@\\341X\\000\\213M\\016\\333\\232N\\262&\\337\\2005:hp\\004\\264\\375\\0106\\362\\204\\015\\000\\004\\020\\3365\\366\\340\\000\\005\\032\\000\\322\\214\\034\\240\\304\\004\\032\\261\\273\\343\\210\\331\\025GL`\\343cS\\272\\036\\037\\\\|\\001\\003\\024\\024\\036\\240^\\022\\276\\236\\022@\\000\\261\\020\\032\\272\\003\\246S`\\217\\203\\221\\201\\203\\221\\025\\274\\030\\001QP\\303\\3620\\264i\\2024\\261\\011\\227gD\\255:aM\\022DY\\217\\264n\\036\\255\\306\\375\\217\\246\\006\\271vF\\237H\\205\\3053#\\343\\177\\006\\3140\\203\\226\\233Hk\\364\\011\\217\\260\\301\\324C\\3640\\003\\353\\010\\016\\016\\026\\370T\\010\\276\\025{\\000\\001\\2047\\313_\\273\\366\\201a\\355\\332\\207P\\203\\230\\2405\\034\\244=\\007_\\266\\010\\265\\030\\342\\031Tqd\\20711A\\312]P%\\002\\031\\301\\373\\217\\022\\370\\220\\212\\211\\001\\034i\\177\\377\\376\\207\\327\\250 >$"\\031\\340l\\360*\\023\\360L43\\230\\375\\007\\\\\\2763\\300=\\012S\\003+:Am\\334\\337\\277!f\\261\\2622A#\\000a.$\\320\\240\\315$\\240\\206\\237?\\1773|\\376\\374\\005<\\302\\364\\367\\357O\\240\\371_\\030**\\334\\030lm\\025\\300\\362\\240\\224\\212+P\\001\\002\\010o\\263\\351\\314\\231\\327\\014\\037>\\374\\202z\\346\\037\\260\\333\\365\\007\\032\\250\\220\\366\\021#t,\\021\\274\\002\\204\\361?<\\265\\200\\002\\207\\211\\211\\021:\\342\\203\\030k\\374\\217\\322\\374\\203\\324\\304 yd\\017\\302"\\0029P`\\233zA\\366B\\314\\207\\0056L\\216\\001\\034\\321\\020q\\006\\270\\033a\\251\\032\\334.\\006\\007\\364_\\260<"\\322\\377!\\261\\031\\340\\376\\004\\2655A\\243\\364\\337\\277\\177a\\370\\372\\025X!\\377\\376\\300\\260b\\005\\007\\203\\2666\\037\\270\\010\\204\\225\\243\\330\\002\\024 \\000\\237V\\220\\0030\\010\\302\\032o\\273\\370\\377\\267:u\\013\\226\\252\\230eW1\\205h\\001k\\370\\177\\330\\027z\\261`k%;\\233\\353]\\005\\304\\200\\305\\206\\356\\354\\263}q\\266a\\352\\217\\347l\\0368\\326\\020\\330\\325|\\356I6\\376\\021,\\034\\371]e\\250{F\\244y@\\272l\\263[/a&\\201\\212)\\324%\\014"`\\023\\035\\304\\273\\221\\3635F\\037\\015O\\335\\376\\253\\216\\276\\002\\010o\\200\\212\\210\\260@S%$[\\375\\371\\003\\235\\332\\375\\307\\200\\350\\345\\374gDI] \\307\\303\\002\\020$\\007[(\\002\\363\\004r\\031\\010KQ\\210\\354\\377\\037)@\\377c\\310CR),\\365"\\273\\003\\0228\\260\\0067\\250hA.\\216`\\211\\002\\265\\005\\200\\310\\342\\360\\346\\0314''@zB\\177\\300\\003, \\032\\024\\240BB<\\340\\201\\021P@\\342\\353z\\002\\004\\020\\3362TD\\204\\015X\\236@\\007-\\376\\375\\207\\227\\241\\340.\\341\\177Dvd\\200\\365~\\240Y\\010\\221"\\021\\251\\017\\221Z\\0311R$\\266\\000E\\257\\311aY\\031\\021\\220\\310)\\232\\001:\\026\\000\\011XX\\221\\000\\233m\\201\\245`D\\266\\376\\217\\024\\311\\214H\\221\\367\\037\\3547\\360,\\300\\237\\337`\\374\\017\\264~\\035\\350.!!\\016\\270\\271\\370Z\\013\\000\\001\\2047@\\245\\2459\\301)\\356\\327\\257\\277\\320\\224\\011\\311\\372\\260r\\023R\\366\\375C\\252\\255\\031\\220*)F\\224\\024\\202(o\\376\\301=\\306''\\310\\301\\240f(\\316 \\245\\310\\017ds\\202G\\341A\\275\\233\\267\\317\\2772\\334\\274\\370\\222\\341\\356\\225WH\\221\\306\\300 ,\\311\\315`\\354 \\317\\300/\\312\\301\\300\\305\\303\\311\\360\\357\\317\\177\\206W\\317>1<\\270\\361\\206\\341\\312\\211g\\014\\337\\277\\375F\\212X\\006\\244HGm6A\\212\\215\\177X\\332\\256\\177\\241\\305\\332\\037h`\\202R\\3427`\\373\\223\\211AA\\201\\037\\261\\343\\030O-\\017\\020@x\\233MBBl\\014\\302\\302\\254\\014\\367\\357\\377\\200\\247DH\\305\\360\\017\\312G8\\206\\211\\211\\021\\251lb\\200VZ\\014\\360\\012\\001\\221\\212!\\346\\363\\012\\2623x\\304\\3520\\360\\362s@\\246\\211\\201\\201\\311\\316\\314\\006N\\0352j\\202\\014R\\312\\374\\014\\234\\274\\254\\014\\027\\016?\\002\\007\\210\\246\\261\\024\\203\\205\\207\\002\\003\\007\\027+"e\\262\\376c\\220U\\025b\\220T\\340cP\\326\\025cX7\\363\\034\\260\\233\\374\\013\\243\\254E\\316\\352\\210T\\213\\332f\\205\\265( \\201\\011\\302?\\3015<\\003\\303\\017\\006))I\\006QQ.\\260?@-\\036|\\023u\\000\\001\\204w\\222\\216\\235\\235\\225AF\\206\\003\\334\\250\\007\\225\\245?~\\374\\0057)~\\377\\376\\003-S\\377\\302\\035\\002b\\203\\002\\373\\317\\037D\\321\\000a\\377\\007\\247j\\020\\033\\022\\031\\020\\032\\22429yX\\301s:\\240\\262\\351\\325\\363\\217\\014\\367\\256\\277b\\370\\003\\336\\035\\007\\351\\367\\353ZJ1\\260\\2601\\203\\307\\016\\314\\\\\\025\\031\\3309Y\\300\\346\\376\\374\\376\\207\\341\\336\\265\\327\\014\\357^\\177\\007\\233\\007\\032W\\020\\223\\346eP\\324\\020\\205\\327\\354 \\373\\020\\025\\327?\\244r\\022\\263\\267\\005\\013\\320?P\\267\\200\\346\\377!k\\000~\\200\\206E\\030\\014\\014\\224\\031@\\013P@)\\023T!\\341\\333\\353\\004\\020@x\\003\\024\\024\\023\\232\\232\\002\\3406\\034\\3102X\\241\\017)Ga1\\012k\\001\\374\\007\\313C\\312\\037X\\213\\000\\035\\377\\207\\353U\\320\\024\\205d\\021Pm\\311\\314\\302\\260}\\311u\\206\\255\\013\\2570\\234?\\362\\004<\\317\\016\\032\\246\\342\\341\\347b\\340\\023\\342\\004\\247\\312\\017o\\2770|\\006\\255X\\001\\272\\345\\374\\341''\\014\\033\\346\\234g8\\262\\3456x\\216\\010\\224\\252\\230\\200\\355HVvfh\\005\\364\\037\\245\\223\\001\\011\\304\\1778\\003\\022\\342/He\\364\\363\\347\\017\\360\\254\\352\\337\\277\\240\\311\\274o\\240\\345\\024\\014\\346\\346j\\360\\360\\000UJ\\370R(@\\000\\341-CA\\032ut\\004\\300Y\\377\\371\\363/\\320\\306/f\\205\\002\\313\\322\\377a\\323\\267\\320\\012\\006\\271\\331\\004\\313\\206\\260b\\342\\350\\266\\333\\0209&`3\\204\\231\\225\\341\\323\\273\\357`5\\177~\\377\\001\\217\\245\\202&\\353~\\003s\\005\\250\\\\\\374\\360\\346\\033\\303\\252\\251g\\200\\201\\317\\014\\014\\\\\\026\\360p\\247\\270,\\037\\203\\266\\231\\0048\\367\\200f?\\177\\000\\325=\\274\\375\\012\\2436Gv+r\\207\\002V\\001!\\002\\375\\037\\270\\334\\204LS\\203R>(@\\2772(*J\\003S\\250\\010<u\\022\\3324\\006\\020@\\004W\\216\\360\\362\\202\\032\\264B\\014\\017\\036\\274\\003;\\034V\\213\\303\\222<,\\226\\341\\303\\262\\214\\3770\\232G\\210\\212\\000Q)\\334\\277\\366\\026I?\\244\\031\\243f \\312``+\\017\\351Q\\201&\\340\\336\\177cx\\367\\352+0\\305B*7P`\\177\\377\\372\\033\\250N\\234\\3017^\\037>\\206\\371\\353\\327o\\2063\\007\\0361\\274}\\361\\015u<\\367\\377\\177\\224\\255\\340\\210\\016\\302_\\214@\\006/\\345\\371\\015\\311\\356\\177\\377\\376\\000\\227\\235\\240\\024jcc\\012l\\3043\\301\\007G\\330\\241\\033sq\\001\\200\\000b"\\024\\240 \\315vv\\022`\\017C\\312\\302\\277H\\364_\\224\\3065$\\326\\031\\300= \\010\\215(7a\\315.D\\363\\344?Ro\\010X^ZH18\\206h\\200\\313I\\360\\270$P\\377\\261\\035w\\200\\201\\371\\017\\336\\033\\202\\265\\032D$y!\\001\\001n\\30033\\260\\263\\2613\\250\\033H0H\\310\\361#U\\230\\250\\373M\\021v\\377\\203\\333\\011\\253H\\377\\200\\327M\\301\\002\\024\\224:\\277\\202\\306\\350\\301\\343\\030vvZ\\360\\201"P`\\302v\\337\\341\\002\\000\\001DT\\200\\202\\312Q\\003`\\352\\001e/H\\345\\363\\027^.\\302\\032\\373\\310="Xy\\205\\332\\260\\206\\264\\021\\377Av\\021\\302+06\\016\\026\\006\\367Hm\\006\\207 \\015\\260CA\\343\\256\\337\\276~g\\330\\271\\342*\\303\\365\\263\\257\\260\\264I\\031\\030\\236\\336{\\307\\260y\\321\\005\\206\\263\\007\\037\\202\\347\\312\\177\\001\\003BH\\234\\213\\301\\326W\\005K\\315\\015)#\\221\\003\\0252\\256\\300\\010\\215\\360\\277\\320\\312\\010Tv\\376\\000\\227\\235\\377\\377C*#kkK\\006%%.\\370H\\023\\362vF\\\\\\000 \\200\\010\\256\\034\\001i\\346\\340`g\\360\\361Qd8~\\37418&!M\\207\\377\\360\\366\\030\\254\\233\\010\\353\\025!\\317k#\\2624\\254\\011\\203h\\217r\\001\\213\\023\\307@5\\006\\025=1p\\355\\012R\\373\\372\\311w\\206\\203\\033o2<\\177\\370\\001\\255\\001\\375\\037\\\\\\373\\203F~\\356^}\\015\\346_9\\371\\214AD\\202\\027\\330t\\022\\004G\\242\\224\\202\\020\\226\\362\\223\\021\\3366E6\\0179\\260a\\201\\371\\373\\367\\027\\240\\030\\250\\330\\370\\010\\016\\232\\340`;p\\340\\203\\022\\025\\250\\357N(\\273\\203\\000@\\000\\021\\265_\\036\\024+FF\\302\\300\\332N\\232\\341\\360\\341\\373\\340\\346\\324\\277\\177L\\320}\\350\\220\\251L\\330 \\010\\242O\\217X\\204\\005)?\\221\\033\\367\\220\\320w\\016U\\003\\007\\006(\\205\\200"\\351\\331\\275\\217\\014;\\226_\\006\\227\\223\\034\\334\\254`s\\276\\177\\371\\305 \\257*\\302`h\\017,[\\231\\3771\\360\\013r\\001\\213\\202{\\014\\327\\316<\\005\\007\\320\\367o?\\240\\203\\341l\\014\\277~\\376\\300\\030\\367\\004\\265\\000\\220\\313Q\\230\\034\\254\\305\\002\\212HP\\315\\376\\353\\327w\\360\\250\\022$0\\17708883\\350\\351\\361\\302\\313NP\\352\\204\\215\\203\\342\\353)\\001\\004\\020Q\\001\\012\\362,77\\007CD\\204*\\303\\211\\023\\217\\300mR\\026\\026\\330\\2105\\242\\241\\213\\260\\207\\021\\243\\341\\214\\234\\375A@IK\\204AFE\\020\\\\\\001\\201\\034\\011\\362\\234\\260$\\017Cd\\2769d\\321-#\\244o\\276\\032X\\273\\177\\372\\360\\235A\\005\\330p\\207\\245*;?5\\006N`\\200\\213\\000{N\\312\\332b\\220\\265\\242\\300\\212\\351\\332\\351g(e(\\362\\321s\\350nA\\317\\352\\277\\177\\177\\002\\312~\\002\\007&?\\277(CV\\226\\023\\270U\\003\\312\\352\\240\\324\\011\\333oO\\350\\000\\002\\200\\000"j\\027\\010l#\\224\\226\\226\\000Ch\\250\\0068V!\\275\\011\\344\\006>j\\023\\005K\\324 \\215,1\\000\\033\\3552(M\\017\\360\\211\\013,\\377\\301)\\023T1\\261q0\\003\\003\\215\\015\\334\\266|\\373\\362+\\303\\301M7\\300\\305\\015(\\220@]V\\307 u\\006}k9\\006V6Vp\\266\\374\\370\\366\\033\\303\\376\\015\\327P*\\035\\364\\301rH@\\376\\203\\326\\001\\220\\300\\374\\371\\363\\033\\020\\177\\002\\312\\201R\\347wp\\331\\031\\037\\037\\310 "\\002io\\202\\374\\015Z\\324\\000[\\312H\\010\\000\\004\\020\\321K\\302A\\331\\033dpH\\210"\\303\\351\\323O\\031._~\\001.[\\021\\331\\350?xA\\027x\\023\\034##Z\\212`@Y\\203\\011\\022\\373\\372\\351\\027\\260\\257\\376\\032\\022a\\240\\021qnf`\\326b\\201WB\\240v\\350_ \\373\\307wH \\036\\337y\\227\\341\\313\\307\\237\\014z\\226\\262\\014\\334\\374\\300T\\303\\305\\006\\236\\243\\374\\014L\\275\\017\\256\\277c8\\265\\357\\016\\270-\\212\\350\\243#\\312JX6\\205\\0046,0\\177\\002\\003\\362;80\\377\\375\\003\\005\\346gp3\\311\\300\\300\\222\\301\\323S\\005\\236\\325A~F\\336XKh\\233\\015@\\000\\341]\\212\\003\\313\\356\\260\\000\\002\\245\\020\\320\\246\\250K\\227^2\\024\\026\\356e\\370\\374\\371''\\264\\241\\313\\014\\357\\222!\\016NA\\237\\307A\\035wD\\214\\226#\\006\\230Q\\003\\377?\\316>7\\372\\034\\021rs\\014y\\320\\030]\\015l\\024\\011\\324<\\002\\245\\314\\037?>\\001\\371\\357\\241\\345\\3467\\006\\001\\001I\\206i\\3232\\031$%!+\\225A\\001\\011Zv\\003Z~\\003\\362''re\\206\\261\\342\\004\\272\\024\\007 \\200\\210\\336\\370\\005K\\245\\240\\321j\\015\\015A\\206\\332Zk\\260\\247A1\\015[\\225\\006[U\\001\\353\\312\\241\\327\\322\\230\\363C05\\377\\340|\\344\\016\\010\\266\\256"\\266Z\\032\\341A\\364qN\\006xy\\011\\013LP\\005\\004\\311\\346_\\200\\374\\217\\320\\224\\011is\\326\\327''0HH \\262:(@A\\376\\205\\225\\235\\304\\000\\200\\000"i''\\035,\\033\\200R\\263\\251\\251\\010Cv\\266\\011\\303W\\320\\202\\327\\237\\210@\\205a\\330r\\025\\364\\362\\024\\321\\036D\\035\\261G\\016(Xs\\007\\221\\352\\376#\\215\\205"cl\\207f\\375\\207\\267\\213a\\033\\027\\376\\202W;\\377\\002g\\361_\\277@)\\363#xZ\\003R\\011}\\007W\\254\\325\\325i\\014\\372\\372|\\340\\300\\004\\371\\021\\024\\230 \\177\\342\\2332\\306\\006\\000\\002\\210\\344\\335\\310\\220v)\\007x\\033t`\\240\\002\\303\\313\\227\\337\\030\\026-:\\215T>\\375\\005\\247d\\210GAe\\352\\177\\350\\264\\002#\\352,\\347\\377\\177\\250m\\314\\177\\014XG\\317\\221S(\\362\\030&bp\\230\\001\\353!\\262\\260\\356%,0!9\\351;8e\\376\\375\\013K\\231\\237\\301v\\307\\304\\20438;\\313\\300\\023\\014,0A\\345''\\261\\033\\276`\\000 \\200H\\016P\\344\\012\\012\\344\\330\\304D\\015\\206\\357\\337\\3772\\254Zu\\006\\230*!s-\\177\\377\\262\\300\\327P\\302\\306\\017a\\345*d\\360\\344?\\332h\\374\\177\\244\\371\\037\\354\\323\\022\\260\\032\\032\\324\\356E\\256\\034\\020e*\\244\\275\\013\\252p`= P\\004\\303\\002\\023\\2242!\\015wX`BF\\342\\203\\202\\002\\031\\342\\342\\014\\340\\275!\\220\\277@\\211\\005\\024\\240\\240\\300%us1@\\000\\221\\275_\\036Vh\\203<\\224\\231\\011\\332\\302\\367\\227a\\311\\222\\363\\340\\254\\016Y\\256\\362\\027\\336`GLj1B\\273m\\214\\030e$l\\320\\0056&\\200\\034\\240\\210\\221rF\\234\\251\\0279\\213C\\232r\\277\\301sB\\220\\341\\270\\257\\300\\000\\376\\012T\\367\\011:$\\367\\035\\354\\365\\270\\270(`\\352\\324\\003\\217\\310\\303\\026u\\300\\002\\223\\334\\3432\\000\\002\\210\\354\\023\\035\\220\\263\\007\\310\\023\\311\\311Z\\014\\342\\342<\\014S\\247\\036\\007\\266\\004\\276\\201\\307)!\\265>\\010\\263\\002\\371\\277\\241l&\\370&\\177D\\377\\237\\021c\\276\\006\\333\\302\\004X\\377\\033y\\254\\000QN\\302\\332\\227\\277\\241\\225\\343Oh\\203\\375+\\264o\\016\\253|\\376\\000\\213,\\001`"\\010\\007w\\247A\\356AN\\231\\374\\374\\374D\\2679\\261\\001\\200\\000\\242\\350\\314\\021X\\203\\037\\344\\020\\020\\360\\367g\\004\\266\\000x\\030::\\216\\003\\333\\251O\\240\\251\\223\\025\\034\\220\\277~\\301F\\272\\231\\241\\355UHj\\205\\3579\\202\\226\\207\\310\\223g\\350\\303\\203\\377\\377#\\246\\261\\0215\\374_xC\\0352\\236\\371\\013\\034\\220\\177\\376|\\205\\216\\270C\\3065!Y\\374\\037\\260\\235i\\302\\220\\227\\347\\315\\240\\240\\300\\205\\221\\315)\\015L\\020\\000\\010 \\212O\\305\\20151@\\016\\0029PK\\213\\231\\241\\277\\337\\221a\\333\\266g\\3006\\335\\001`[\\365#0%\\263\\303\\313Q\\320~NHJ\\205\\235\\246\\310\\004\\237\\370\\202\\315\\371 \\312Y\\344J\\0131#\\011^]\\012\\235L\\003\\245H\\004\\015\\031\\313\\374\\377\\377;4\\000\\177B\\003\\36470\\320D\\031bc\\275\\031\\374\\374\\324\\201l\\026xm\\016\\012LP\\026\\007\\271\\037\\304\\246$0A\\000 \\200\\250r\\020\\026\\310\\021\\260\\203O`efh(\\033\\203\\216\\216\\037\\303\\342\\305\\227\\031\\366\\356\\275\\002l\\252\\374\\006\\212\\263\\301\\003\\021\\026\\270\\240\\365\\231\\240\\300E,\\211d\\200\\316\\347\\203\\002\\365/<u\\302\\266{C\\002\\363\\0174p\\177\\201\\313\\311\\377\\377!\\0304]\\001\\012<H9\\371\\023\\234\\275\\231\\2308\\031\\254\\255m\\031\\222\\222\\354\\031\\344\\3459\\341#\\357\\240D\\000*3A\\201\\011+3I\\255\\321\\261\\001\\200\\000\\242\\332\\311b\\2602\\025\\346`PV\\322\\323cehl\\344\\005v\\345\\224\\0306n\\274\\311p\\374\\370\\015\\206o\\240\\223\\031\\031Y\\301Y\\037\\022h\\260\\212\\212\\011\\261\\356\\024\\266\\177\\035ee\\012\\010\\377\\201\\256\\011\\000\\341\\337\\320@c\\204\\246\\302_P>x\\273\\0320\\200\\004\\031\\314\\315\\365\\031\\302\\302\\254\\03145\\371\\300E\\014lN\\010\\224\\255Ae?r\\303\\235\\322\\224\\011\\003\\000\\001D\\325\\263\\357`e\\022\\214\\206M\\031\\330\\331\\2611\\230\\231\\2111\\334\\277o\\310p\\360\\340C\\206\\235;/2<x\\360\\002\\032(\\320\\215,\\360\\271(&\\264\\336\\023#t\\333\\000\\3444\\007X\\200\\301R \\322zop\\204HII\\003\\3553epw\\327b\\220\\223\\343\\201w\\237a\\363A\\260\\2769-\\216i\\003\\001\\200\\000"j\\363,\\271\\345*\\254\\234\\002a\\320\\342+uu6`e\\300\\015,\\016T\\300+\\373\\216\\037\\277\\313p\\345\\312#\\206{\\367\\2361|\\371\\362\\021\\032@\\377\\220\\002\\221\\011>\\030\\215\\032x\\260\\261\\001\\220=<@3\\345\\200e\\267\\034\\203\\245\\245\\032\\260\\230\\021\\004\\006\\0243\\312\\034:l<\\023\\024\\230\\260\\221#\\330I\\015\\244\\370\\361?\\021''\\252\\003\\004\\020M\\002\\024\\275\\003\\000\\313f\\240\\345\\201\\220\\275\\347?\\200)\\226\\203\\301\\320P\\030X#\\0331|\\370\\360\\207\\341\\341\\303\\217\\300\\024\\374\\232\\341\\315\\233O@\\376W\\240\\332\\037\\300@\\376\\311\\360\\376\\375{\\3604\\013''''d\\325\\033''''\\023x\\341\\226\\240 \\037\\203\\232\\232\\024\\203\\252*h\\360\\202\\011\\274L\\021V\\271!\\247HP*\\004\\331\\015\\243a\\001Ih\\\\\\223\\334p\\000\\010 \\026b\\014An\\306\\220\\333\\011\\200\\225_ \\217\\201\\372\\376\\240\\271 \\020\\015\\302\\234\\234\\177\\030\\304\\3048\\031\\214\\214D1\\006\\205qy\\004y\\0055\\254]\\213\\034\\220\\240\\034\\202\\034\\210\\310\\363\\351\\377\\3118\\273\\237\\330\\273Q\\000\\002\\210\\205Z\\006\\021;\\225\\002\\253aA\\036\\3056\\240\\202\\274\\240\\002\\327\\211\\341\\310\\233$`\\331\\032V\\021\\302f&a\\201\\210\\274\\342\\370?\\035.A\\000\\010 \\026z\\337\\374\\002+\\012\\220\\3136X \\242\\007(\\276\\261G\\364\\354\\015K\\2010\\263\\321Ww\\320\\353\\274{\\200\\000b\\031\\250\\203\\365\\221S\\027(0\\320\\347\\316\\361]C\\204\\276\\225\\007\\226\\345\\351y\\236=.\\000\\020@,\\203\\345\\272\\012X\\000\\017u\\000\\020@L\\243\\367\\177P\\027\\000\\004\\020hc6\\013z\\3159\\012\\310\\313a@\\314\\002\\020@,\\277\\377\\374y\\373\\353\\347\\317??\\311\\030L\\035\\005\\250\\001\\012l\\251|\\004\\0100\\000f\\237&\\210\\264U[\\366\\000\\000\\000\\000IEND\\256B`\\202', '1', '1af86cee0f9f04731e397b688a47e8f8', '2009-01-18 15:53:39.765', NULL, 'Vorabversion des großen Logos');


--
-- Data for Name: a23_filestore_container; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_filestore_container (tag_id, file_id, filestore_container_id) VALUES (4, 4, 1);
INSERT INTO a23_filestore_container (tag_id, file_id, filestore_container_id) VALUES (4, 5, 2);


--
-- Data for Name: a23_global_conf; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_global_conf (conf_id, name_space, conf_type, conf_value) VALUES (1, 'themes', 'themename', 'Arbeitsmarkt');
INSERT INTO a23_global_conf (conf_id, name_space, conf_type, conf_value) VALUES (2, 'themes', 'sucher', 'Bewerber');
INSERT INTO a23_global_conf (conf_id, name_space, conf_type, conf_value) VALUES (3, 'themes', 'angebot', 'Stelle');
INSERT INTO a23_global_conf (conf_id, name_space, conf_type, conf_value) VALUES (4, 'themes', 'anbieter', 'Firma');
INSERT INTO a23_global_conf (conf_id, name_space, conf_type, conf_value) VALUES (5, 'themes', 'kontaktaufnahme', 'Bewerbung');
INSERT INTO a23_global_conf (conf_id, name_space, conf_type, conf_value) VALUES (6, 'themes', 'kategorie', 'Beruf');
INSERT INTO a23_global_conf (conf_id, name_space, conf_type, conf_value) VALUES (7, 'themes', 'sucher_p', 'Bewerber');
INSERT INTO a23_global_conf (conf_id, name_space, conf_type, conf_value) VALUES (8, 'themes', 'angebot_p', 'Stellen');
INSERT INTO a23_global_conf (conf_id, name_space, conf_type, conf_value) VALUES (9, 'themes', 'anbieter_p', 'Firmen');
INSERT INTO a23_global_conf (conf_id, name_space, conf_type, conf_value) VALUES (10, 'themes', 'kontaktaufnahme_p', 'Bewerbungen');
INSERT INTO a23_global_conf (conf_id, name_space, conf_type, conf_value) VALUES (11, 'themes', 'kategorie_p', 'Berufe');


--
-- Data for Name: a23_handicap; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Arbeitsbereich: Minijob', 2);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Arbeitszeit: Schichtdienst', 3);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Arbeitszeit: Teilzeit', 4);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Arbeitszeit: Wochenendarbeit', 5);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Arbeitszeit: Zeitarbeit', 6);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Arbeitsbereich: Umgang mit ätzenden Stoffen', 13);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Arbeitsbereich: Umgang mit gefährlichen Stoffen', 14);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Arbeitsbereich: langes Sitzen', 15);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Arbeitsbereich: langes Stehen', 16);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Arbeitsbereich: schweres Heben', 17);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Arbeitsbereich: Schwindelfreiheit', 18);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Arbeitsbereich: Umgang mit giftigen Stoffen', 20);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Arbeitsbereich: Umgang mit minder-giftigen Stoffen', 21);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Arbeitsbereich: Umgang mit gefährlichen Personen', 22);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Arbeitsbereich: Tiere', 23);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Arbeitsbereich: Lärm', 24);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Arbeitsbereich: Schmutz', 25);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Handicap: blind', 26);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Handicap: eingeschränkte Bewegungsfähigkeit', 27);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Handicap: Auffassungsgabe', 29);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Handicap: Gehen', 28);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Handicap: Hören', 30);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Handicap: Sehen', 31);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Handicap: sehr klein', 32);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Handicap: sehr groß', 33);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Handicap: Tourette-Syndrom', 34);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Gesundheit: Asthmatiker', 35);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Gesundheit: Allergiker', 36);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Gesundheit: Depressionen', 37);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Gesundheit: Klaustrophobie', 38);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Überzeugung: Individualist', 39);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Überzeugung: Rassist', 40);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Überzeugung: Tierfreund', 41);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Überzeugung: Veganer', 42);
INSERT INTO a23_handicap (handicap_type, handicap_id) VALUES ('Lohn/Gehalt: Muss Geld mitbringen', 43);


--
-- Data for Name: a23_industry; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Andere', 1);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Bau: Anlagen- u. Einrichtungsbau', 2);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Bau: Architekten / Bauingenieure', 3);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Bau: Bauhauptgewerbe', 4);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Bau: Baunebengewerbe', 5);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Bau: Baustoffe / Baubedarf', 6);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Bau: Elektrotechnik', 7);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Bau: Heizung / Sanitärtechnik', 8);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Bau: Hochbau', 9);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Bau: Immobilien', 10);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Bau: Innenarchitektur', 11);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Bau: Klimatechnik / Belüftung', 12);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Bau: Maschinenbau u. Betriebstechnik', 13);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Bau: Schiffsbau', 14);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Bau: Technische Gebäudeausrüstung', 15);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Bau: Tiefbau', 16);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Bau: Trockenbau', 17);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Behörden u. Verbände: Behörden', 18);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Behörden u. Verbände: Bürgerinitiativen u. soziale Einrichtungen', 19);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Behörden u. Verbände: Verbände / Vereine / Gemeinnützige Einrichtungen', 20);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Bildung u. Wissenschaft: Beruf / Karriere', 21);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Bildung u. Wissenschaft: Hochschulen / Wissenschaft / Forschung', 22);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Bildung u. Wissenschaft: Marktforschung', 23);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Bildung u. Wissenschaft: Unterricht / Erziehung', 24);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Computer: Computer u. Netzwerksicherheit', 25);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Computer: E-Learning', 26);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Computer: Hardware', 27);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Computer: Software', 28);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Computer: Spiele', 29);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Dienstleistungen: Abfallwirtschaft', 30);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Dienstleistungen: Beratung', 31);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Dienstleistungen: Bürodienstleistungen', 32);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Dienstleistungen: Call-Center', 33);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Dienstleistungen: Coaching', 34);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Dienstleistungen: Ermittlungen / Sicherheit / Schutz', 35);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Dienstleistungen: Finanzdienstleistungen', 36);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Dienstleistungen: Hauswirtschaft', 37);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Dienstleistungen: Information / Dokumentation', 38);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Dienstleistungen: Ingenieurbüros', 39);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Dienstleistungen: Kosmetik', 40);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Dienstleistungen: Plakate / Schilder / Beschriftung', 41);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Dienstleistungen: Reinigung / Wartung / Pflege', 42);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Dienstleistungen: Sachverständige', 43);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Dienstleistungen: Schlüssel / Schlösser', 44);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Dienstleistungen: Schreiben u. Lektorat', 45);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Dienstleistungen: Technische Dienstleistungen', 46);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Dienstleistungen: Verleih und Vermietung', 47);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Dienstleistungen: Öffentlicher Dienst', 48);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Dienstleistungen: Öffentlichkeitsarbeit u. Kommunikation', 49);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Dienstleistungen: Übersetzung u. Lokalisierung', 50);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Elektronik: Audio / Video', 51);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Elektronik: Elektronik / Elektrotechnik', 52);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Elektronik: Foto', 53);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Elektronik: Internet', 54);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Elektronik: Messtechnik / Regeltechnik', 55);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Elektronik: Telekommunikation', 56);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Freizeit u. Tourismus: Camping / Caravaning', 57);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Freizeit u. Tourismus: Erotik', 58);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Freizeit u. Tourismus: Fitness und Sport', 59);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Freizeit u. Tourismus: Freizeiteinrichtungen u. –dienstleistungen', 60);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Freizeit u. Tourismus: Glücksspiel / Wetten / Lotterie', 61);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Freizeit u. Tourismus: Hobby- / Freizeitaktivitäten', 62);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Freizeit u. Tourismus: Hobby- / Freizeitbedarf', 63);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Freizeit u. Tourismus: Kultur', 64);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Freizeit u. Tourismus: Reisen', 65);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Freizeit u. Tourismus: Sportartikel und -bekleidung', 66);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Geld u. Recht: Akquise / Fundraising', 67);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Geld u. Recht: Anlage / Finanzierung', 68);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Geld u. Recht: Rechnungswesen', 69);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Geld u. Recht: Recht / Rechtsberatung', 70);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Geld u. Recht: Steuerberatung', 71);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Geld u. Recht: Versicherungen', 72);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Gesundheit: Alternative Behandlungsmethoden', 73);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Gesundheit: Arzneimittel / Heil- und Hilfsmittel', 74);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Gesundheit: Betreuung / Pflege / Lebenshilfe', 75);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Gesundheit: Ernährung und Gewichtsabnahme', 76);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Gesundheit: Fitness und Sport', 77);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Gesundheit: Kinderbetreuung', 78);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Gesundheit: Krankenhäuser und Kliniken', 79);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Gesundheit: Krankenversicherungen', 80);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Gesundheit: Medizinische Dienste', 81);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Gesundheit: Medizinische Geräte', 82);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Gesundheit: Medizinische Rechtsbereiche', 83);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Gesundheit: Psychologie und Psychiatrie', 84);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Gesundheit: Schwangerschaft und Geburt', 85);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Gesundheit: Schönheit und Körperpflege', 86);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Gesundheit: Sportmedizin', 87);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Gesundheit: Therapie / Reha / Kur', 88);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Gesundheit: Tiermedizin', 89);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Gesundheit: Wellness und Gesundheitsvorsorge', 90);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Gesundheit: Zahnmedizin und -ästhetik', 91);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Gesundheit: Ärzte und medizinische Dienste', 92);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Bankwesen', 93);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Bekleidung', 94);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Bücher / Datenträger', 95);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Bürobedarf / Schreibwaren', 96);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Einzelhandel', 97);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Getränke', 98);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Großhandel', 99);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Haushaltsgeräte / Hausrat', 100);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Immobilien', 101);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Import u. Export', 102);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Investment Banking', 103);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Lebensmittel', 104);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Leder / Lederwaren', 105);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Luxusgüter u. Schmuck', 106);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Marketing u. Werbung', 107);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Möbel', 108);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Reinigungsmittel', 109);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Schuhe und Zubehör', 110);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Spielwaren', 111);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Tabakwaren / Raucherbedarf', 112);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Textilien', 113);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Venture Capital u. Private Equity', 114);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Wein- u. Spirituosen', 115);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Handel: Weitere Handelsgeschäfte', 116);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Hotels u. Gastronomie: Bars / Diskotheken', 117);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Hotels u. Gastronomie: Cafés / Kneipen', 118);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Hotels u. Gastronomie: Gaststätten / Restaurants', 119);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Hotels u. Gastronomie: Hotels / Pensionen', 120);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Hotels u. Gastronomie: Lieferservice / Catering', 121);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Automatisierungstechnik', 122);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Biotechnologie', 123);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Chemische Industrie', 124);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Energiewirtschaft / Erneuerbare Energien', 125);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Fischerei', 126);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Glas u. Keramik', 127);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Halbleiter', 128);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Holzwerkstoffindustrie', 129);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Industrie allgemein', 130);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Kunststofftechnik', 131);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Metallindustrie / -verarbeitung', 132);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Mode / Bekleidungsindustrie', 133);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Möbelindustrie', 134);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Nanotechnologie', 135);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Papier- u. Forstprodukte', 136);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Pharmazeutische Industrie', 137);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Textilindustrie', 138);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Lebensmittel', 139);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Elektrotechnik', 140);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Verbundwerkstoffe', 141);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Versorgungswirtschaft', 142);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Verteidigung / Militär', 143);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Industrie: Elektronik', 144);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Kultur: Esoterik', 145);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Kultur: Film / Musik', 146);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Kultur: Kunst / Kunsthandwerk / Design', 147);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Kultur: Museen u. Kultureinrichtungen', 148);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Kultur: Theater / Bühne / Kino', 149);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Kultur: Unterhaltung', 150);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Kultur: Veranstaltungen', 151);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Kultur: Veranstaltungstechnik', 152);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Medien: Bibliotheken', 153);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Medien: Druck / Graphisches Gewerbe', 154);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Medien: Fotografie', 155);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Medien: Journalismus', 156);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Medien: Medienproduktion', 157);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Medien: Onlinemedien', 158);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Medien: Printmedien / Verlagswesen', 159);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Medien: Rundfunk u. Fernsehen', 160);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Medien: Telekomunikation', 161);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Medien: Tontechnik', 162);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Medien: Unterhaltung', 163);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Medien: Werbung / Werbemittel', 164);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Natur u. Umwelt: Bergbau', 165);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Natur u. Umwelt: Energie', 166);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Natur u. Umwelt: Gartenbau', 167);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Natur u. Umwelt: Gartenbedarf', 168);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Natur u. Umwelt: Landwirtschaft', 169);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Natur u. Umwelt: Pflanzen / Blumen', 170);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Natur u. Umwelt: Recycling u. Entsorgung', 171);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Natur u. Umwelt: Rohstoffe', 172);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Natur u. Umwelt: Steine / Erde / Mineralien', 173);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Natur u. Umwelt: Tierhaltung / Tierzucht', 174);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Natur u. Umwelt: Umweltschutz / Umweltdienste', 175);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Politik: Internationale Angelegenheiten', 176);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Politik: Internationaler Handel u. Entwicklung', 177);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Politik: Nationale Angelegenheiten', 178);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Politik: Nationaler Handel u. Entwicklung', 179);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Transport u. Verkehr: Automobilindustrie', 180);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Transport u. Verkehr: Eisenbahn', 181);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Transport u. Verkehr: Fahrzeuge', 182);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Transport u. Verkehr: Fluggesellschaften', 183);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Transport u. Verkehr: Logistik u. Zulieferung', 184);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Transport u. Verkehr: Luft- und Raumfahrt', 185);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Transport u. Verkehr: Seefahrt', 186);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Transport u. Verkehr: Transport / Verkehr', 187);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Transport u. Verkehr: Transportbedarf', 188);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Transport u. Verkehr: Verkehrstechnik', 189);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Transport u. Verkehr: Versand u. Container', 190);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Abfallwirtschaft / Geräte und Zubehör', 191);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Automaten', 192);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Baumaschinen', 193);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Beschichtung', 194);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Bürobedarf', 195);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Bürodienstleistungen', 196);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Chemie / Chemische Technik', 197);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Gastronomiebedarf', 198);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Gewerbebedarf', 199);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Kunststoffe / Gummi', 200);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Laden- / Betriebseinrichtung', 201);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Landwirtschaftlicher Bedarf', 202);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Management', 203);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Maschinen', 204);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Maschinenteile', 205);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Mechanische Bearbeitung', 206);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Mess- und Regeltechnik', 207);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Metall', 208);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Outsourcing / Offshoring', 209);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Personalbeschaffung', 210);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Personalwesen', 211);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Personalwirtschaft', 212);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Prozessmanagement', 213);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Rechnungswesen', 214);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Reinigungsmaschinen', 215);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Steuerberatung / Wirtschaftsprüfung', 216);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Unternehmensberatung / Consulting', 217);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Veranstaltungsdienstleistungen', 218);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Verkehrstechnische Ausstattungen', 219);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Verpackungsarbeiten', 220);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Verpackungsbedarf', 221);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Unternehmensbedarf: Werkzeuge', 222);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Wohnen: Haushaltsgeräte / Hausrat', 223);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Wohnen: Innenarchitektur', 224);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Wohnen: Licht / Beleuchtung', 225);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Wohnen: Möbel', 226);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Wohnen: Raumausstattung', 227);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (4, 'Handel: Lebensmittel', 228);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (4, 'Industrie: Lebensmittel', 229);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (4, 'Natur u. Umwelt: Landwirtschaft', 230);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (4, 'Natur u. Umwelt: Tierhaltung / Tierzucht', 231);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (5, 'Dienstleistungen: Lieferservive / Botendienste', 232);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (5, 'Transport u. Verkehr: Logistik u. Zulieferung', 233);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (3, 'Dienstleistungen: Lieferservive / Botendienste', 234);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (6, 'Dienstleistungen: Reinigung / Wartung / Pflege', 235);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (7, 'Gesundheit: Betreuung / Pflege / Lebenshilfe', 236);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (8, 'Kultur: Unterhaltung', 237);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (8, 'Kultur: Theater / Bühne / Kino', 238);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (9, 'Dienstleistungen: Call-Center', 239);
INSERT INTO a23_industry (provider_id, industry_identifier, industry_id) VALUES (9, 'Handel: Marketing u. Werbung', 240);


--
-- Data for Name: a23_newsletter_log; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_newsletter_log (newsletter_id, subject, newsletter_body, sent_from, create_date, editor_id) VALUES (1, '[artikel23] - Rundschreiben', 'hallo!', '', '2009-02-27 10:47:33.764913', -1);
INSERT INTO a23_newsletter_log (newsletter_id, subject, newsletter_body, sent_from, create_date, editor_id) VALUES (2, '[artikel23] - Rundschreiben', 'hallo!!', '', '2009-02-27 10:49:17.463522', -1);
INSERT INTO a23_newsletter_log (newsletter_id, subject, newsletter_body, sent_from, create_date, editor_id) VALUES (3, '[artikel23] - Rundschreiben', 'Hallo!!!', '', '2009-02-27 10:51:15.970253', -1);
INSERT INTO a23_newsletter_log (newsletter_id, subject, newsletter_body, sent_from, create_date, editor_id) VALUES (4, '[artikel23] - Rundschreiben', 'Hallo !!!!!', '', '2009-02-27 10:53:45.98375', -1);
INSERT INTO a23_newsletter_log (newsletter_id, subject, newsletter_body, sent_from, create_date, editor_id) VALUES (5, '[artikel23] - Rundschreiben', 'Hallo!!2', '', '2009-02-27 10:55:22.449197', -1);
INSERT INTO a23_newsletter_log (newsletter_id, subject, newsletter_body, sent_from, create_date, editor_id) VALUES (6, '[artikel23] - Rundschreiben', 'hftkzuhf', '', '2009-02-27 10:56:48.141768', -1);
INSERT INTO a23_newsletter_log (newsletter_id, subject, newsletter_body, sent_from, create_date, editor_id) VALUES (7, '[artikel23] - Rundschreiben', 'trallala!!', '', '2009-02-27 10:57:48.052887', -1);
INSERT INTO a23_newsletter_log (newsletter_id, subject, newsletter_body, sent_from, create_date, editor_id) VALUES (8, '[artikel23] - Rundschreiben', 'drghaerdgt', '', '2009-02-27 11:04:44.511786', -1);
INSERT INTO a23_newsletter_log (newsletter_id, subject, newsletter_body, sent_from, create_date, editor_id) VALUES (9, '[artikel23] - Rundschreiben', 'etgewrg', '', '2009-02-27 11:05:27.199579', -1);
INSERT INTO a23_newsletter_log (newsletter_id, subject, newsletter_body, sent_from, create_date, editor_id) VALUES (10, '[artikel23] - Rundschreiben', 'dthradth', '', '2009-02-27 11:08:37.120885', -1);
INSERT INTO a23_newsletter_log (newsletter_id, subject, newsletter_body, sent_from, create_date, editor_id) VALUES (11, '[artikel23] - Rundschreiben', 'öuigljg', '', '2009-02-27 11:11:19.899294', -1);
INSERT INTO a23_newsletter_log (newsletter_id, subject, newsletter_body, sent_from, create_date, editor_id) VALUES (12, '[artikel23] - Rundschreiben', 'Tärähhh!!', 'briefkasten@olaf-radicke.de', '2009-02-27 11:27:15.312677', -1);
INSERT INTO a23_newsletter_log (newsletter_id, subject, newsletter_body, sent_from, create_date, editor_id) VALUES (13, '[artikel23] - Rundschreiben', 'izglg', 'briefkasten@olaf-radicke.de', '2009-02-27 11:31:57.499653', -1);
INSERT INTO a23_newsletter_log (newsletter_id, subject, newsletter_body, sent_from, create_date, editor_id) VALUES (14, '[artikel23] - Rundschreiben', 'jhvjlh.', 'olaf_rad@gmx.de', '2009-02-27 11:33:59.183078', -1);
INSERT INTO a23_newsletter_log (newsletter_id, subject, newsletter_body, sent_from, create_date, editor_id) VALUES (15, '[artikel23] - Rundschreiben', 'jblbh', 'olaf_rad@gmx.de', '2009-02-27 11:35:24.437362', -1);
INSERT INTO a23_newsletter_log (newsletter_id, subject, newsletter_body, sent_from, create_date, editor_id) VALUES (16, '[artikel23] - Rundschreiben', 'gukjdzuk', 'olaf_rad@gmx.de', '2009-02-27 12:09:47.305816', -1);


--
-- Data for Name: a23_newsletter_sent_to_seeker; Type: TABLE DATA; Schema: public; Owner: -
--



--
-- Data for Name: a23_offer; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_offer (offer_id, offers_date, info_source, provider_id, job_count, salutation, note) VALUES (3, '2009-01-12', 'Morgenpost', 3, 1, 'Keine Angabe', 'Achtung: Dummy AG dient als Platzhalter zur Aufnahme der Branchenbezeicjnungen!');
INSERT INTO a23_offer (offer_id, offers_date, info_source, provider_id, job_count, salutation, note) VALUES (4, '2009-01-12', 'Zeit', 4, 1, 'Frau', 'Die Flädle Nudelwaren AG ist weltweit eine der führenden Flädle-Hersteller.
Die Umgebung dort unten ist wunderschön.
Unterkunft wird laut Anzeige gestellt.');
INSERT INTO a23_offer (offer_id, offers_date, info_source, provider_id, job_count, salutation, note) VALUES (5, '2009-01-12', 'Drosselmarscher Bote', 5, 2, 'Herr', 'Wenn alle Stricke reißen...');
INSERT INTO a23_offer (offer_id, offers_date, info_source, provider_id, job_count, salutation, note) VALUES (6, '2009-01-12', 'Niederhammelner Anzeiger', 6, 1, 'Keine Angabe', 'Oh Mann, wo soll das enden?');
INSERT INTO a23_offer (offer_id, offers_date, info_source, provider_id, job_count, salutation, note) VALUES (7, '2009-01-12', 'Fareweller Bote', 7, 3, 'Keine Angabe', 'Ob ich meine Omma dort unterbringen würde?');
INSERT INTO a23_offer (offer_id, offers_date, info_source, provider_id, job_count, salutation, note) VALUES (8, '2009-01-12', 'Knüppeldicker Kurier', 8, 1, 'Herr', 'Hab ich schon mal besucht als ich noch klein war, ist klasse! Kann ich nur empfehlen! Hans Rüdiger');
INSERT INTO a23_offer (offer_id, offers_date, info_source, provider_id, job_count, salutation, note) VALUES (9, '2009-01-12', 'jobshooter.de', 9, 1, 'Herr', 'Au weia!');


--
-- Data for Name: a23_offer_link_to_handicap; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_offer_link_to_handicap (offer_id, handicap_id, offer_handicap_id) VALUES (5, 3, 1);
INSERT INTO a23_offer_link_to_handicap (offer_id, handicap_id, offer_handicap_id) VALUES (5, 4, 2);
INSERT INTO a23_offer_link_to_handicap (offer_id, handicap_id, offer_handicap_id) VALUES (5, 5, 3);
INSERT INTO a23_offer_link_to_handicap (offer_id, handicap_id, offer_handicap_id) VALUES (5, 6, 4);
INSERT INTO a23_offer_link_to_handicap (offer_id, handicap_id, offer_handicap_id) VALUES (6, 16, 5);
INSERT INTO a23_offer_link_to_handicap (offer_id, handicap_id, offer_handicap_id) VALUES (6, 25, 6);
INSERT INTO a23_offer_link_to_handicap (offer_id, handicap_id, offer_handicap_id) VALUES (6, 17, 7);
INSERT INTO a23_offer_link_to_handicap (offer_id, handicap_id, offer_handicap_id) VALUES (6, 21, 8);
INSERT INTO a23_offer_link_to_handicap (offer_id, handicap_id, offer_handicap_id) VALUES (6, 3, 9);
INSERT INTO a23_offer_link_to_handicap (offer_id, handicap_id, offer_handicap_id) VALUES (6, 5, 10);
INSERT INTO a23_offer_link_to_handicap (offer_id, handicap_id, offer_handicap_id) VALUES (6, 6, 11);
INSERT INTO a23_offer_link_to_handicap (offer_id, handicap_id, offer_handicap_id) VALUES (7, 17, 12);
INSERT INTO a23_offer_link_to_handicap (offer_id, handicap_id, offer_handicap_id) VALUES (9, 2, 13);
INSERT INTO a23_offer_link_to_handicap (offer_id, handicap_id, offer_handicap_id) VALUES (9, 5, 14);
INSERT INTO a23_offer_link_to_handicap (offer_id, handicap_id, offer_handicap_id) VALUES (9, 6, 15);


--
-- Data for Name: a23_offer_link_to_quality; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (4, 9, 1);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (4, 15, 2);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (4, 20, 3);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (4, 49, 4);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (4, 50, 5);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (4, 51, 6);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (4, 52, 7);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (4, 54, 8);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (4, 55, 9);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (4, 56, 10);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (4, 59, 11);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (4, 60, 12);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (4, 62, 13);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (4, 65, 14);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (4, 68, 15);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (4, 90, 16);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (4, 133, 17);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (4, 135, 18);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (4, 136, 19);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (4, 161, 20);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (5, 7, 21);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (5, 10, 22);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (5, 54, 23);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (5, 57, 24);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (5, 59, 25);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (5, 61, 26);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (5, 62, 27);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (5, 67, 28);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (6, 9, 29);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (6, 24, 30);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (6, 26, 31);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (6, 61, 32);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (7, 9, 33);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (7, 20, 34);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (7, 49, 35);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (7, 51, 36);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (7, 64, 37);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (8, 5, 38);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (8, 9, 39);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (8, 20, 40);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (8, 51, 41);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (8, 52, 42);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (8, 56, 43);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (8, 58, 44);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (8, 67, 45);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (9, 8, 46);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (9, 24, 47);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (9, 49, 48);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (9, 55, 49);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (9, 56, 50);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (9, 58, 51);
INSERT INTO a23_offer_link_to_quality (offer_id, quality_id, offer_quality_id) VALUES (9, 86, 52);


--
-- Data for Name: a23_offer_link_to_stuff; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_offer_link_to_stuff (stuff_id, offer_id, offer_stuff_id) VALUES (70, 3, 1);
INSERT INTO a23_offer_link_to_stuff (stuff_id, offer_id, offer_stuff_id) VALUES (181, 4, 2);
INSERT INTO a23_offer_link_to_stuff (stuff_id, offer_id, offer_stuff_id) VALUES (256, 4, 3);
INSERT INTO a23_offer_link_to_stuff (stuff_id, offer_id, offer_stuff_id) VALUES (15, 5, 4);
INSERT INTO a23_offer_link_to_stuff (stuff_id, offer_id, offer_stuff_id) VALUES (16, 5, 5);
INSERT INTO a23_offer_link_to_stuff (stuff_id, offer_id, offer_stuff_id) VALUES (15, 6, 6);
INSERT INTO a23_offer_link_to_stuff (stuff_id, offer_id, offer_stuff_id) VALUES (283, 6, 7);
INSERT INTO a23_offer_link_to_stuff (stuff_id, offer_id, offer_stuff_id) VALUES (1, 7, 8);
INSERT INTO a23_offer_link_to_stuff (stuff_id, offer_id, offer_stuff_id) VALUES (2, 7, 9);
INSERT INTO a23_offer_link_to_stuff (stuff_id, offer_id, offer_stuff_id) VALUES (3, 7, 10);
INSERT INTO a23_offer_link_to_stuff (stuff_id, offer_id, offer_stuff_id) VALUES (300, 8, 11);
INSERT INTO a23_offer_link_to_stuff (stuff_id, offer_id, offer_stuff_id) VALUES (46, 9, 12);


--
-- Data for Name: a23_provider; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_provider (provider_id, district, name, street, housenumber, zip_code, city, member_count, parent_company, note) VALUES (1, '', 'Altenheim Sedavit GmbH', 'Baldrianstr.', '15', '12453', 'Berlin', 4, NULL, 'Test');
INSERT INTO a23_provider (provider_id, district, name, street, housenumber, zip_code, city, member_count, parent_company, note) VALUES (4, '', 'Flädle Nudelwaren AG', 'Wuallene Gasse ', '3-5', '80344', 'Wualla im Allgäu', 0, NULL, '');
INSERT INTO a23_provider (provider_id, district, name, street, housenumber, zip_code, city, member_count, parent_company, note) VALUES (5, '', 'Quicky Lieferservice GmbH', 'Trödelstr. ', '12', '23234', 'Lahmarsch an der Drossel', 0, NULL, '');
INSERT INTO a23_provider (provider_id, district, name, street, housenumber, zip_code, city, member_count, parent_company, note) VALUES (3, '', 'Dummy AG', 'Dummystr.', '1', '11111', 'Dummydorf', 0, NULL, '');
INSERT INTO a23_provider (provider_id, district, name, street, housenumber, zip_code, city, member_count, parent_company, note) VALUES (6, '', 'Lollipop AG', 'Prenzelstr. ', '5', '23456', 'Zweibisdreisiedeln', 0, NULL, '');
INSERT INTO a23_provider (provider_id, district, name, street, housenumber, zip_code, city, member_count, parent_company, note) VALUES (7, '', 'Altenheim SedaVit Ltd.', 'Am Ende ', '7', '42344', 'Oberfarewell', 0, NULL, '');
INSERT INTO a23_provider (provider_id, district, name, street, housenumber, zip_code, city, member_count, parent_company, note) VALUES (9, '', 'Musterfirma Ltd.', 'Lauterstr. ', '5-34', '52121', 'Neppernich', 0, NULL, '');
INSERT INTO a23_provider (provider_id, district, name, street, housenumber, zip_code, city, member_count, parent_company, note) VALUES (8, '', 'Trallala GmbH', 'Kasperlestr.', '12', '32121', 'Knüppeldick', 0, NULL, 'Wäre doch was für Horst! Anrufen!');


--
-- Data for Name: a23_provider_black_list; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_provider_black_list (provider_id, provider_black_list_id) VALUES (3, 1);


--
-- Data for Name: a23_provider_domain; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_provider_domain (provider_id, domain_name) VALUES (4, 'www.flaedle-nudle.de');
INSERT INTO a23_provider_domain (provider_id, domain_name) VALUES (5, 'www.quicky-lvsvc.de');
INSERT INTO a23_provider_domain (provider_id, domain_name) VALUES (8, 'www.trallala-unterhaltung-fuer-die-kleinsten.de');


--
-- Data for Name: a23_provider_filestore; Type: TABLE DATA; Schema: public; Owner: -
--



--
-- Data for Name: a23_provider_member; Type: TABLE DATA; Schema: public; Owner: -
--



--
-- Data for Name: a23_provider_member_email; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_provider_member_email (provider_id, member_id, email_local_part, email_domain, email_id) VALUES (4, NULL, 'info', 'flaedle-nudle.de', 1);
INSERT INTO a23_provider_member_email (provider_id, member_id, email_local_part, email_domain, email_id) VALUES (5, NULL, 'info', 'quicky-lvsvc.de', 2);
INSERT INTO a23_provider_member_email (provider_id, member_id, email_local_part, email_domain, email_id) VALUES (8, NULL, 'tritra', 'trallala.de', 3);


--
-- Data for Name: a23_provider_member_phone; Type: TABLE DATA; Schema: public; Owner: -
--



--
-- Data for Name: a23_provider_phone; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_provider_phone (provider_id, phone_no, fax_or_phone, country_code, area_code, direct_inward_dialing, provider_phone_id) VALUES (1, '0303784320', '', '', '', '', 1);
INSERT INTO a23_provider_phone (provider_id, phone_no, fax_or_phone, country_code, area_code, direct_inward_dialing, provider_phone_id) VALUES (1, '03037843215', '', '', '', '', 2);
INSERT INTO a23_provider_phone (provider_id, phone_no, fax_or_phone, country_code, area_code, direct_inward_dialing, provider_phone_id) VALUES (4, '087349877', '', '', '', '', 3);
INSERT INTO a23_provider_phone (provider_id, phone_no, fax_or_phone, country_code, area_code, direct_inward_dialing, provider_phone_id) VALUES (4, '0873487565', '', '', '', '', 4);
INSERT INTO a23_provider_phone (provider_id, phone_no, fax_or_phone, country_code, area_code, direct_inward_dialing, provider_phone_id) VALUES (5, '02217873322', '', '', '', '', 5);
INSERT INTO a23_provider_phone (provider_id, phone_no, fax_or_phone, country_code, area_code, direct_inward_dialing, provider_phone_id) VALUES (6, '0234487655', '', '', '', '', 6);
INSERT INTO a23_provider_phone (provider_id, phone_no, fax_or_phone, country_code, area_code, direct_inward_dialing, provider_phone_id) VALUES (7, '0473768774', '', '', '', '', 7);
INSERT INTO a23_provider_phone (provider_id, phone_no, fax_or_phone, country_code, area_code, direct_inward_dialing, provider_phone_id) VALUES (8, '03766506', '', '', '', '', 8);


--
-- Data for Name: a23_provider_pobox; Type: TABLE DATA; Schema: public; Owner: -
--



--
-- Data for Name: a23_quality; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Abgeschlossenes Studium', 4);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Alter ab 50', 5);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Alter bis 25', 6);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Alter bis 30', 7);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Alter bis 40', 8);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Alter bis 50', 9);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Arbeitsbereich: Außendienst', 10);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Arbeitsbereich: Freiberufler', 11);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Arbeitsbereich: Geschäftsführung', 12);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Arbeitsbereich: Innendienst', 13);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Arbeitsbereich: Praktikum', 14);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Arbeitsbereich: Projektplanung', 15);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Arbeitsbereich: Projektkoordinierung', 16);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Arbeitsbereich: Psycho-soziale Betreuung', 17);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Arbeitszeit: Vollzeit', 20);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bescheinigung: Basisqualifikation für Pfegekräfte', 22);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bescheinigung: Behindertenausweis', 23);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bescheinigung: Förderung durch JobCenter', 24);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bescheinigung: Förderung nach SGB II', 25);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bescheinigung: Förderung nach SGB III', 26);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bescheinigung: Förderung nach SGB IV', 27);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bescheinigung: Förderung nach SGB V', 28);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bescheinigung: Förderung nach SGB VI', 29);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bescheinigung: Förderung nach SGB VIII', 30);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bescheinigung: Gabelstaplerschein', 31);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bescheinigung: Gesellenbrief', 32);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bescheinigung: Gesundheitspass', 33);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bescheinigung: Kassenpass', 34);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bescheinigung: Meisterbrief', 35);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bescheinigung: Personenbeförderungsschein', 36);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bescheinigung: Prüfungszertifikat der Deutschen Klassenlotterie', 37);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bescheinigung: Teilnahme an Telefonseminaren', 38);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bescheinigung: Vermittlungsgutschein', 39);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bundesland: Berlin', 40);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bundesland: Brandenburg', 41);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bundesland: Bundesweit', 42);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Graduierung: Techniker', 43);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Graduierung: Dr.', 44);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Graduierung: Dipl.-Ing.', 45);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Graduierung: Dipl.-Ing. (FH)', 46);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Graduierung: Prof.', 47);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Graduierung: Prof. Dr.', 48);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: belastbar', 49);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: ehrlich', 50);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: einfühlsam', 51);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: flexibel', 52);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: Führungseigenschaften', 53);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: gewissenhaft', 54);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: kommunikationsstark', 55);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: kontaktfähig', 56);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: kräftig', 57);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: kreativ', 58);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: Kunden- und Service-orientiert', 59);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: lernwillig', 60);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: mobil', 61);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: pünktlich', 62);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: rationelles Arbeiten', 63);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: selbständiges Arbeiten', 64);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: sorgfältig', 65);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: soziale Kompetenz', 66);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: teamfähig', 67);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: verantwortungsbereit', 68);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: zeitlich flexibel', 69);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: zuverlässig', 70);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Führerschein: Kl. A (Motorrad)', 71);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Führerschein: Kl. B', 72);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Führerschein: Kl. C (über 7,5t)', 73);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Informatik: Grundkenntnisse', 74);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Informatik: Studium', 75);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Kenntnisse: Ausländerrecht', 76);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Kenntnisse: Ausländerrecht (Grundlagen)', 77);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Kenntnisse: Digitaler Schnitt', 78);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Kenntnisse: Sehr gute Fachkenntnisse', 79);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Kenntnisse: Gästebetreuung', 80);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Kenntnisse: Gesundheits- und Sozialwesen', 81);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Kenntnisse: Kameraarbeit', 82);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Kenntnisse: Kongress-Organisation', 83);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Kenntnisse: Kundenberatung', 84);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Kenntnisse: Lohnbuchhaltung', 85);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Kenntnisse: Marketing, PR', 86);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Kenntnisse: Medizinischer Bereich', 87);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Kenntnisse: PC-Hardware', 88);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Kenntnisse: Stenografie', 89);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Kenntnisse: Schreibmaschine', 90);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Kenntnisse: Tontechnik', 91);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Kenntnisse: Umgang mit der Motorsäge', 92);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Kenntnisse: Verkauf', 93);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Kenntnisse: Volkswirtschaft', 94);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Ortskkenntnisse im Voralpenraum', 95);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Ortskkenntnisse in Brandenburg', 96);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Ortskkenntnisse in und um Berlin', 97);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: allgemein', 98);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: ASP', 99);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: C', 100);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: C#', 101);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: C++', 102);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: CSS', 103);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: Delphi', 104);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: HTML', 105);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: Java2', 106);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: JavaScript', 107);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: JSP', 108);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: Pascal', 109);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: Perl', 110);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: Perl/CGI', 111);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: PHP', 112);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: PHP/CGI', 113);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: SAP', 114);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: SQL', 115);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: TurboPascal', 116);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: Typo3', 117);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: XML', 118);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: XSL', 119);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Programmierkenntnisse: XSLT', 120);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Schulabschluss: Abitur', 121);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Schulabschluss: Andere', 122);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Schulabschluss: Fachhochschule', 123);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Schulabschluss: Fachoberschule', 124);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Schulabschluss: Grundschule', 125);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Schulabschluss: Hauptschule', 126);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Schulabschluss: Hochschule', 127);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Schulabschluss: Realschule', 128);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Softwarekenntnisse: Bildbearbeitung', 129);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Softwarekenntnisse: CAD/CAM', 130);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Softwarekenntnisse: Domus', 131);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Softwarekenntnisse: Internet', 132);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Softwarekenntnisse: MS Excel', 133);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Softwarekenntnisse: MS Access', 134);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Softwarekenntnisse: MS Office', 135);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Softwarekenntnisse: MS Office, Internet', 136);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Softwarekenntnisse: MS Powerpoint', 137);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Softwarekenntnisse: MS Project', 138);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Softwarekenntnisse: PC allgemein', 139);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Softwarekenntnisse: SAP', 140);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Softwarekenntnisse: SUMA-Lagersoftware', 141);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Softwarekenntnisse: Typo3', 142);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Sprachkenntnisse: Albanisch', 143);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Sprachkenntnisse: Arabisch', 144);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Sprachkenntnisse: Deutsch', 145);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Sprachkenntnisse: Englisch', 146);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Sprachkenntnisse: Englisch (Grundkenntnisse)', 147);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Sprachkenntnisse: Englisch (fließend in Wort und Schrift)', 148);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Sprachkenntnisse: Französisch', 149);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Sprachkenntnisse: Italienisch', 150);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Sprachkenntnisse: Japanisch', 151);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Sprachkenntnisse: Koreanisch', 152);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Sprachkenntnisse: Polnisch', 153);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Sprachkenntnisse: Russisch', 154);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Sprachkenntnisse: Russisch (Verständnis)', 155);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Sprachkenntnisse: Spanisch', 156);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Sprachkenntnisse: Tunesisch', 157);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Sprachkenntnisse: Türkisch', 158);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Sprachkenntnisse: Twi (Ghana)', 159);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Voraussetzung: gepflegtes Äußeres', 161);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Voraussetzung: eigener PKW', 160);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Arbeitsbereich: Lehre', 162);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: schwindelfrei', 165);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Voraussetzung: Karate', 166);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Voraussetzung: Vollkontaktkarate', 167);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bescheinigung: Waffenschein', 168);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: gutes Sehvermögen', 169);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: gutes Gehör', 170);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Bescheinigung: Tauchschein', 171);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Person: Rentner', 172);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Eigenschaft: Tierfreund', 173);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Softwarekenntnisse: MS Word', 174);
INSERT INTO a23_quality (quality_type, quality_id) VALUES ('Ehrenamtlicher Mitarbeiter', 175);


--
-- Data for Name: a23_request; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_request (seeker_id, editor_id, request_id, request_date, situation, note, offer_id) VALUES (9, 7, 6, '2009-01-12', 'Bewerbung initiiert', 'Will die Stelle nur annehmen, wenn er bis zur Vorstellung nichts besseres findet.', 6);
INSERT INTO a23_request (seeker_id, editor_id, request_id, request_date, situation, note, offer_id) VALUES (6, 7, 7, '2009-01-12', 'Bewerbung initiiert', '', 4);


--
-- Data for Name: a23_seeker; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_seeker (seeker_no, seeker_id, name, street, housenumber, zip_code, city, birthday, salutation, joining, priority, note, address_addition) VALUES ('5', 5, 'Rank,Anja', 'Inselstr.', '10', '10585', 'Berlin', '1960-10-12', 'Frau', '2008-03-06', 75, 'Am besten zu erreichen in den Sprechzeiten: 9-13 Uhr', '');
INSERT INTO a23_seeker (seeker_no, seeker_id, name, street, housenumber, zip_code, city, birthday, salutation, joining, priority, note, address_addition) VALUES ('8', 8, 'Mustermann,Benno', 'Oberurseler Allee', '234', '13345', 'Hamburg', '1958-04-03', 'Herr', '2008-11-18', 75, 'Wird leicht ungeduldig', '');
INSERT INTO a23_seeker (seeker_no, seeker_id, name, street, housenumber, zip_code, city, birthday, salutation, joining, priority, note, address_addition) VALUES ('7', 7, 'Mustermann,Heinz', 'Labskauser Str.', '26', '44658', 'Hamburg', '1962-12-07', 'Herr', '2008-11-18', 50, 'Momentan noch verantwortlich für IT von Trödel Lempke', '');
INSERT INTO a23_seeker (seeker_no, seeker_id, name, street, housenumber, zip_code, city, birthday, salutation, joining, priority, note, address_addition) VALUES ('-1', -1, 'anonymous,', '', '', '0', '', '1753-01-01', '', '2009-01-18', 0, 'Vom System angelegter Sucher für Aktivitäten von Unbekannten', '');
INSERT INTO a23_seeker (seeker_no, seeker_id, name, street, housenumber, zip_code, city, birthday, salutation, joining, priority, note, address_addition) VALUES ('6', 6, 'Stütz,Lisa', 'Hanselstr.', '1', '12115', 'Berlin', '1967-08-19', 'Frau', '2008-12-11', 50, 'Sprechzeiten: 8-10 Uhr', '');
INSERT INTO a23_seeker (seeker_no, seeker_id, name, street, housenumber, zip_code, city, birthday, salutation, joining, priority, note, address_addition) VALUES ('9', 9, 'Testermann,Kuno', 'Teststr.', '132', '12233', 'Berlin', '1966-11-13', 'Herr', '2008-12-27', 75, 'Test... Test...
Test...', '');


--
-- Data for Name: a23_seeker_filestore; Type: TABLE DATA; Schema: public; Owner: -
--



--
-- Data for Name: a23_seeker_link_to_handicap; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_seeker_link_to_handicap (seeker_id, handicap_id, seeker_handicap_id) VALUES (5, 6, 1);
INSERT INTO a23_seeker_link_to_handicap (seeker_id, handicap_id, seeker_handicap_id) VALUES (8, 36, 4);
INSERT INTO a23_seeker_link_to_handicap (seeker_id, handicap_id, seeker_handicap_id) VALUES (7, 2, 5);
INSERT INTO a23_seeker_link_to_handicap (seeker_id, handicap_id, seeker_handicap_id) VALUES (7, 17, 6);
INSERT INTO a23_seeker_link_to_handicap (seeker_id, handicap_id, seeker_handicap_id) VALUES (7, 33, 7);
INSERT INTO a23_seeker_link_to_handicap (seeker_id, handicap_id, seeker_handicap_id) VALUES (7, 39, 8);
INSERT INTO a23_seeker_link_to_handicap (seeker_id, handicap_id, seeker_handicap_id) VALUES (6, 24, 9);
INSERT INTO a23_seeker_link_to_handicap (seeker_id, handicap_id, seeker_handicap_id) VALUES (6, 4, 10);


--
-- Data for Name: a23_seeker_link_to_quality; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (5, 54, 1);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (5, 51, 2);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (5, 49, 3);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (5, 56, 4);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (5, 57, 5);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (5, 60, 6);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (5, 64, 7);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (5, 65, 8);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (5, 66, 9);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (5, 67, 10);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (5, 68, 11);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (5, 69, 12);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (5, 70, 13);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (5, 72, 14);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (5, 17, 15);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (5, 20, 16);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (8, 20, 33);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (8, 161, 34);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (8, 160, 35);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (8, 147, 36);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (8, 128, 37);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (8, 86, 38);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (7, 4, 39);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (7, 11, 40);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (7, 20, 41);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (7, 75, 42);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (7, 100, 43);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (7, 102, 44);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (7, 104, 45);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (7, 106, 46);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (7, 109, 47);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (7, 115, 48);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (7, 116, 49);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (7, 127, 50);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (7, 139, 51);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (7, 145, 52);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (7, 148, 53);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (7, 160, 54);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (7, 161, 55);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (6, 8, 56);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (6, 20, 57);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (6, 50, 58);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (6, 51, 59);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (6, 52, 60);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (6, 53, 61);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (6, 54, 62);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (6, 68, 63);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (6, 70, 64);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (6, 83, 65);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (6, 85, 66);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (6, 124, 67);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (6, 135, 68);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (6, 145, 69);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (6, 148, 70);
INSERT INTO a23_seeker_link_to_quality (seeker_id, quality_id, seeker_quality_id) VALUES (6, 161, 71);


--
-- Data for Name: a23_seeker_link_to_stuff; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_seeker_link_to_stuff (stuff_id, seeker_id, seeker_stuff_id) VALUES (1, 5, 3);
INSERT INTO a23_seeker_link_to_stuff (stuff_id, seeker_id, seeker_stuff_id) VALUES (11, 8, 6);
INSERT INTO a23_seeker_link_to_stuff (stuff_id, seeker_id, seeker_stuff_id) VALUES (22, 8, 7);
INSERT INTO a23_seeker_link_to_stuff (stuff_id, seeker_id, seeker_stuff_id) VALUES (43, 8, 8);
INSERT INTO a23_seeker_link_to_stuff (stuff_id, seeker_id, seeker_stuff_id) VALUES (45, 8, 9);
INSERT INTO a23_seeker_link_to_stuff (stuff_id, seeker_id, seeker_stuff_id) VALUES (48, 8, 10);
INSERT INTO a23_seeker_link_to_stuff (stuff_id, seeker_id, seeker_stuff_id) VALUES (216, 7, 11);
INSERT INTO a23_seeker_link_to_stuff (stuff_id, seeker_id, seeker_stuff_id) VALUES (230, 7, 12);
INSERT INTO a23_seeker_link_to_stuff (stuff_id, seeker_id, seeker_stuff_id) VALUES (15, -1, 13);
INSERT INTO a23_seeker_link_to_stuff (stuff_id, seeker_id, seeker_stuff_id) VALUES (231, 6, 16);
INSERT INTO a23_seeker_link_to_stuff (stuff_id, seeker_id, seeker_stuff_id) VALUES (256, 6, 17);
INSERT INTO a23_seeker_link_to_stuff (stuff_id, seeker_id, seeker_stuff_id) VALUES (15, 9, 18);
INSERT INTO a23_seeker_link_to_stuff (stuff_id, seeker_id, seeker_stuff_id) VALUES (283, 9, 19);


--
-- Data for Name: a23_seeker_logbook; Type: TABLE DATA; Schema: public; Owner: -
--



--
-- Data for Name: a23_seeker_phone; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (-1, 'Privat:', 23, '');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (-1, 'Büro:', 24, '');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (-1, 'Fax:', 25, '');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (-1, 'Mobile:', 26, '');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (-1, 'AIM:', 27, '');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (-1, 'ICQ:', 28, '');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (-1, 'Skype:', 29, '');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (-1, 'Website:', 30, '');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (-1, 'MailTo:anon@anon-mail.de', 31, '');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (-1, '', 32, '');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (9, 'olaf_rad@gmx.de', 34, 'MailTo');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (6, '030345667', 35, 'Privat');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (6, 'test2@test-mail.de', 36, 'MailTo');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (6, '03056735698', 37, 'Freund');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (6, '03034547456', 38, 'Bei Muttern');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (9, '0304535667', 39, 'Privat');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (8, 'test4@test-mail.de', 40, 'MailTo');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (8, '030455656', 41, 'Privat');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (7, '0404532667', 44, 'Privat');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (7, 'test3@test-mail.de', 45, 'MailTo');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (5, '03045982762', 46, 'Privat');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (5, 'test1@test-mail.de', 47, 'MailTo');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (5, '03034238734', 48, 'Freund');
INSERT INTO a23_seeker_phone (seeker_id, phone_no, phone_id, fax_or_phone) VALUES (5, '0304523234', 49, 'Büro');


--
-- Data for Name: a23_stuff_type; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (1, 'Altenpflegehelfer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (2, 'Altenpfleger/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (3, 'Altenpfleger/in, exam.');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (4, 'Angestellte/r Datenverarbeitung');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (5, 'Anlagenmechaniker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (6, 'Apothekenhelfer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (7, 'Arzt/Ärztin - Assistenz');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (8, 'Arzt/Ärztin');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (9, 'Arzthelfer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (10, 'Asphaltbauer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (11, 'Assistent/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (12, 'Aufbereitungsmechankier/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (13, 'Augenoptiker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (14, 'Ausbaufacharbeiter/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (15, 'Aushilfen');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (16, 'Auslieferungsfahrer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (17, 'Ausschneider/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (18, 'Außendienstmitarbeiter/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (19, 'Bademeister/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (20, 'Bandagist/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (21, 'Bankkaufmann/-frau');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (22, 'Barkeeper/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (23, 'Bauhelfer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (24, 'Bauingenieur/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (25, 'Bauleiter/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (26, 'Bauzeichner/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (27, 'Beamter/Beamtin');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (28, 'Berater/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (29, 'Berufskraftfahrer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (30, 'Bestattungsfachkraft');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (31, 'Beton- u. Stahlbetonbauer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (32, 'Betriebswirt/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (33, 'Bodenleger/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (34, 'Bootsbauer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (35, 'Bote/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (36, 'Briefträger/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (37, 'Buchbinder/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (38, 'Buchhalter/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (39, 'Buchhändler/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (40, 'Bäcker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (41, 'Bühnentechniker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (42, 'Bürofachkraft');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (43, 'Bürohelfer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (44, 'Bürokaufmann/-frau');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (45, 'Bürokraft');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (46, 'Call-Center Mitarbeiter/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (47, 'Catering-Berater/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (48, 'Chauffeur/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (49, 'Chemielaborant/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (50, 'Chemiker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (51, 'Controller/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (52, 'Dachdecker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (53, 'Dekorateur/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (54, 'Designer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (55, 'Dipl.-Betriebswirt/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (56, 'Dipl.-Ingenieur/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (57, 'Dipl.-Maschinenbau- u. Wirtschaftsingenieur/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (58, 'Dipl.-Musiker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (59, 'Dipl.-Sachverständige/r Immobilien');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (60, 'Diplombetriebswirt/ in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (61, 'Diplompsychologe/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (62, 'Disponent/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (63, 'Dokumentarfilmer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (64, 'Dolmetscher/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (65, 'Dozent/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (66, 'Drechsler/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (67, 'Dreher/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (68, 'Drogist/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (69, 'Drucker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (70, 'Eierlegende Wollmilchsau');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (71, 'Einzelhandelskaufmann/-frau');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (72, 'Eisenbahner/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (73, 'Eisenbieger/in u. -flechter/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (74, 'Elektroanlagenmonteur/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (75, 'Elektrofachkraft');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (76, 'Elektroinstallateur/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (77, 'Elektromechaniker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (78, 'Elektroniker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (79, 'Empfangsmitarbeiter/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (80, 'Ergotherapeut/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (81, 'Erzieher/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (82, 'Erzähler/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (83, 'Eventmanager/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (84, 'Fachangestellte/r für Bürokommunikation');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (85, 'Facharzt/ärztin Arbeitsmedizin');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (86, 'Fachinformatiker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (87, 'Fachverkäufer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (88, 'Fahrer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (89, 'Fahrzeugschlosser/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (90, 'Fertigungsmechaniker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (91, 'Finanz- u. Lohnbuchhalter/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (92, 'Fleischer (Ausschneider)');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (93, 'Fleischer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (94, 'Fliesen-/Plattenleger/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (95, 'Florist/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (96, 'Flugbegleiter/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (97, 'Fotograf/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (98, 'Fotolaborant/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (99, 'Fremdsprachenkorrespondent/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (100, 'Fremdsprachensekretär/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (101, 'Friseur/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (102, 'Friseurmeister/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (103, 'Fräser/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (104, 'Fußbodenleger/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (105, 'Fußpfleger/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (106, 'Förderlehrer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (107, 'Gabelstaplerfahrer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (108, 'Galvaniseur/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (109, 'Gartenbauhelfer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (110, 'Gas- u. Wasserinstallateur/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (111, 'Gastronom/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (112, 'Gebietsbeauftragte');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (113, 'Gebäudereiniger/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (114, 'Geigenbauer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (115, 'Gerichtsvollzieher/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (116, 'Gerüstbauer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (117, 'Gesundheits- u. Kinderkrankenpfleger/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (118, 'Gitarrenlehrer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (119, 'Glaser/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (120, 'Goldschmied/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (121, 'Grafik-Designer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (122, 'Groß- u. Außenhandelskaufmann/frau');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (123, 'Großhandelskaufmann/-frau');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (124, 'Gärtner/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (125, 'Handwerker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (126, 'Hauselektriker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (127, 'Hausmeister/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (128, 'Hauswirtschafter/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (129, 'Hebamme');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (130, 'Heilerziehungspfleger/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (131, 'Heizungsbauer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (132, 'Hochschulagraringenieur/in für Tierproduktion');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (133, 'Hotelfachmann/-frau');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (134, 'Hotelkaufmann/-frau');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (135, 'Imbissverkäufer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (136, 'Immobilienkaufmann/-frau');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (137, 'Industriekaufmann/-frau');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (138, 'Industriemechaniker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (139, 'Informationselektroniker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (140, 'Ingenieur/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (141, 'Isolierer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (142, 'IT-Systemelektroniker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (143, 'Journalist/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (144, 'Justizfachangestellte/r');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (145, 'Kalt-Akquisiteur/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (146, 'Kameramann/-frau');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (147, 'Kanalbauer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (148, 'Kapitän/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (149, 'Karosserie- u. Fahrzeugbauer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (150, 'Kaufmann/-frau');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (151, 'Kaufmann/frau der Grundstücks- u. Wohnungswirtschaft');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (152, 'Kaufmann/frau für Bürokommunikation');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (153, 'Kellner/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (154, 'Kfz-Lackierer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (155, 'Kinderkrankenschwester/-pfleger');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (156, 'Kinderpfleger/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (157, 'Klavier- u. Cembalobauer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (158, 'Klempner/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (159, 'Koch/Köchin');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (160, 'Kommissionär/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (161, 'Kommunikationselektroniker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (162, 'Koordinator/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (163, 'Kosmetiker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (164, 'Kraftfahrer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (165, 'Kraftfahrzeugmechaniker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (166, 'Kraftfahrzeugmechatroniker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (167, 'Krankenpflegehelfer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (168, 'Krankenschwester/-pfleger');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (169, 'Krankenschwester/-pfleger, exam.');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (170, 'Krankenschwesterhelferin');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (171, 'Krankentransport- u. Telebusfahrer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (172, 'Kundenbetreuer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (173, 'Kurierfahrer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (174, 'Kutscher/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (175, 'Kälteanlagenbauer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (176, 'Körperpsychotherapeut/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (177, 'Küchenhilfe');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (178, 'Landschaftsgärtner/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (179, 'Landwirtschaftshelfer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (180, 'Lehrer/in für Bürokommunikation');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (181, 'Leiter/in Organisation');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (182, 'Lektor/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (183, 'Maler/in u. Lackierer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (184, 'Maler/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (185, 'Marketing-und Vertriebskoordinator/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (186, 'Maschinenbauer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (187, 'Masseur/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (188, 'Maurer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (189, 'Maßschneider/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (190, 'Mechaniker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (191, 'Metallbauer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (192, 'Mitarbeiter für Möbelhandel');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (193, 'Mitarbeiter/in Datenmanagement');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (194, 'Mitarbeiter/in Disposition u. Auftragsannahme');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (195, 'Mitarbeiter/in IT-Support');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (196, 'Mitarbeiter/in Koordination Vertrieb digitale Medien');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (197, 'Mitarbeiter/in Lager- u. Transportbereich');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (198, 'Mitarbeiter/in Modegeschäft');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (199, 'Mitarbeiter/in Portyfoliomanagement');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (200, 'Mitarbeiter/in Projektierung');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (201, 'Mitarbeiter/in Property Management');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (202, 'Mitarbeiter/in Versicherung');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (203, 'Musik-Therapeut/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (204, 'Möbeltischler/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (205, 'Nachrichtengerätemechaniker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (206, 'Notarfachangestellte/r');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (207, 'Näher/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (208, 'Objektverwalter/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (209, 'Optiker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (210, 'Orchesterwart/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (211, 'Orthopädiemechaniker/in u. Bandagist/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (212, 'Orthopädieschuhmacher/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (213, 'Paketzusteller/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (214, 'Parkettleger/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (215, 'Pastor/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (216, 'PC-Administrator/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (217, 'Personalbetreuerin');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (218, 'Pferdewirt/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (219, 'Pflegedienstleitung');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (220, 'Pflegehelfer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (221, 'Pförtner/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (222, 'Pharmazeutisch-technische/r Assistent/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (223, 'Physiotherapeut/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (224, 'Pilot/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (225, 'Podologe/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (226, 'Polier/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (227, 'Polsterer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (228, 'Praktikant/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (229, 'Produktionshelfer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (230, 'Programmierer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (231, 'Projektmanager/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (232, 'Qualitätsmanagager/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (233, 'Radio- u. Fernsehtechniker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (234, 'Radiologieassistent/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (235, 'Raumausstatter/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (236, 'Rechtsanwalts- u. Notarfachangestellte/r');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (237, 'Rechtsanwaltsfachangestellte/r');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (238, 'Redakteur/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (239, 'Reinigungskraft');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (240, 'Reiseverkehrskaufmann/-frau');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (241, 'Reporter/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (242, 'Restaurantfachmann/-frau');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (243, 'Rettungssanitäter/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (244, 'Rohrleitungsbauer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (245, 'Rollladen- u. Jalousiebauer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (246, 'Sanitäter/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (247, 'Schauspieler/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (248, 'Schauwerbegestalter/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (249, 'Schilder- u. Lichtreklamehersteller/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (250, 'Schlachter/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (251, 'Schlosser/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (252, 'Schneider/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (253, 'Schornsteinfeger/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (254, 'Schuhmacher/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (255, 'Schweißer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (256, 'Sekretär/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (257, 'Seniorenhelferin');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (258, 'Servicekraft');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (259, 'Speditionskaufmann/frau');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (260, 'Spielhallenaufsicht');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (261, 'Sprachmittler/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (262, 'Staplerfahrer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (263, 'Steinmetz/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (264, 'Steuerfachangestellte/r');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (265, 'Storemanager/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (266, 'Straßenbauer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (267, 'Stuckateur/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (268, 'Systemelektroniker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (269, 'Tankwart/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (270, 'Taxifahrer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (271, 'Techniker/in Heizungs/Lüftungs/Klimatechnik');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (272, 'Techniker/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (273, 'Technische/r Assistent/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (274, 'Technische/r Zeichner/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (275, 'Theaterpädergoge/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (276, 'Tierarzt/-ärztin');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (277, 'Tierpflegehelfer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (278, 'Tierwirt/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (279, 'Tischler/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (280, 'Tischlerhelfer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (281, 'Tresenkraft');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (282, 'Trockenbaumonteur/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (283, 'Ungelernt');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (284, 'Veranstaltungskaufmann/frau');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (285, 'Verkäufer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (286, 'Versicherungsfachmann/fachfrau');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (287, 'Vertriebsmitarbeiter/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (288, 'Verwaltungsangestellte/r');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (289, 'Videothekar/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (290, 'Webdeveloper/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (291, 'Wohnbereichsleiter/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (292, 'Zahnarzthelfer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (293, 'Zentralheizungs-und Lüftungsbauer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (294, 'Zimmermädchen');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (295, 'Änderungsschneider/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (296, 'Übersetzer/in Muttersprache Slowenisch');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (297, 'Übersetzer/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (299, 'Schausteller/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (300, 'Puppenspieler/in');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (301, 'Dipl.-Bauingenieur/in, Tiefbau');
INSERT INTO a23_stuff_type (stuff_id, stuff_type) VALUES (302, 'Dipl.-Bauingenieur/in, Hochbau');


--
-- Data for Name: a23_version; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO a23_version (major_release, minor_release, patch_level, a23_version_id) VALUES (1, 0, 0, 9);


--
-- Data for Name: game_funk; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO game_funk (nachrichten_id, nachrichten_text) VALUES (1, '11.04.2008 16:37:54 Boot-ID -1:

klklklklk');


--
-- Data for Name: game_landkarte; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO game_landkarte (objekt_name, geo_data, spiel_name) VALUES ('england', '((550,350),(650,350),(600,475),(725,475),(650,650),(720,710),(750,800),(800,850),(850,950),(830,1000),(900,970),(960,1000),(900,1150),(680,1210),(650,1180),(570,1250),(450,1250),(550,1125),(500,1100),(550,1050),(550,925),(650,900),(600,830),(630,750),(525,750),(450,660),(550,350))', 'UK_cup');
INSERT INTO game_landkarte (objekt_name, geo_data, spiel_name) VALUES ('hebriden', '((470,370),(400,450),(400,600),(470,370))', 'UK_cup');
INSERT INTO game_landkarte (objekt_name, geo_data, spiel_name) VALUES ('orkneys', '((670,270),(670,330),(600,330),(670,270))', 'UK_cup');
INSERT INTO game_landkarte (objekt_name, geo_data, spiel_name) VALUES ('shetland', '((775,100),(750,225),(720,150),(775,100))', 'UK_cup');
INSERT INTO game_landkarte (objekt_name, geo_data, spiel_name) VALUES ('irland', '((375,700),(440,720),(500,800),(440,880),(470,930),(400,1050),(200,1125),(150,1050),(200,1000),(250,930),(170,900),(225,800),(375,700))', 'UK_cup');
INSERT INTO game_landkarte (objekt_name, geo_data, spiel_name) VALUES ('eu_festland', '((500,1460),(500,1410),(750,1410),(710,1300),(850,1325),(960,1240),(960,1200),(1050,1220),(1500,800),(2100,600),(2100,2550),(650,2550),(700,1950),(500,1560))', 'UK_cup');


--
-- Data for Name: game_spieler; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO game_spieler (mitglieds_id, "position", proviant, zustand, segelflaeche, segelstellung, kurs, spielzug_abgeschlossen, geplanter_route) VALUES (7, '(970,1000)', 100, 100, 0, 0, 0, 0, '((970,1000),(970,1000))');


--
-- Data for Name: game_werte; Type: TABLE DATA; Schema: public; Owner: -
--

INSERT INTO game_werte (bezeichner, text_wert, int_wert) VALUES ('zeitintervall', 'h', 8);
INSERT INTO game_werte (bezeichner, text_wert, int_wert) VALUES ('ausgangs_temperatur', 'Grad-Celsius-50', 60);
INSERT INTO game_werte (bezeichner, text_wert, int_wert) VALUES ('kartengroesse', '1100:1550', 0);
INSERT INTO game_werte (bezeichner, text_wert, int_wert) VALUES ('szenario_name', 'UK_cup', 0);
INSERT INTO game_werte (bezeichner, text_wert, int_wert) VALUES ('sturmtief', '59:1147', 0);
INSERT INTO game_werte (bezeichner, text_wert, int_wert) VALUES ('runden_zahl', '', 3);
INSERT INTO game_werte (bezeichner, text_wert, int_wert) VALUES ('windrichtung', '(315,0°) -NW ', 3150);
INSERT INTO game_werte (bezeichner, text_wert, int_wert) VALUES ('windstaerke', 'h', 3);
INSERT INTO game_werte (bezeichner, text_wert, int_wert) VALUES ('niederschlag', 'przent', 0);
INSERT INTO game_werte (bezeichner, text_wert, int_wert) VALUES ('sichtweite', 'meter', 1500);
INSERT INTO game_werte (bezeichner, text_wert, int_wert) VALUES ('temperatur', 'Grad-Celsius-50', 54);


--
-- Name: a23_file_reserve_file_id_key; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_file_reserve
    ADD CONSTRAINT a23_file_reserve_file_id_key UNIQUE (file_id);


--
-- Name: a23_file_reserve_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_file_reserve
    ADD CONSTRAINT a23_file_reserve_pkey PRIMARY KEY (a23_file_reserve_id);


--
-- Name: a23_newsletter_log_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_newsletter_log
    ADD CONSTRAINT a23_newsletter_log_pkey PRIMARY KEY (newsletter_id);


--
-- Name: a23_newsletter_sent_to_seeker_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_newsletter_sent_to_seeker
    ADD CONSTRAINT a23_newsletter_sent_to_seeker_pkey PRIMARY KEY (a23_newsletter_sent_to_seeker_id);


--
-- Name: a23_provider_filestore_filestore_id_key; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_provider_filestore
    ADD CONSTRAINT a23_provider_filestore_filestore_id_key UNIQUE (filestore_id);


--
-- Name: a23_provider_filestore_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_provider_filestore
    ADD CONSTRAINT a23_provider_filestore_pkey PRIMARY KEY (link_id);


--
-- Name: a23_provider_phone_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_provider_phone
    ADD CONSTRAINT a23_provider_phone_pkey PRIMARY KEY (provider_phone_id);


--
-- Name: a23_seeker_filestore_filestore_id_key; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_seeker_filestore
    ADD CONSTRAINT a23_seeker_filestore_filestore_id_key UNIQUE (filestore_id);


--
-- Name: a23_seeker_filestore_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_seeker_filestore
    ADD CONSTRAINT a23_seeker_filestore_pkey PRIMARY KEY (link_id);


--
-- Name: a23_seeker_logbook_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_seeker_logbook
    ADD CONSTRAINT a23_seeker_logbook_pkey PRIMARY KEY (log_id);


--
-- Name: a23_version_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_version
    ADD CONSTRAINT a23_version_pkey PRIMARY KEY (a23_version_id);


--
-- Name: activity_activity_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_activity_activity
    ADD CONSTRAINT activity_activity_pkey PRIMARY KEY (activity_activity_id);


--
-- Name: activity_container_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_activity_container
    ADD CONSTRAINT activity_container_pkey PRIMARY KEY (activity_container_id);


--
-- Name: activity_filestore_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_activity_filestore
    ADD CONSTRAINT activity_filestore_pkey PRIMARY KEY (activity_filestore_id);


--
-- Name: activity_firma_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_activity_provider
    ADD CONSTRAINT activity_firma_pkey PRIMARY KEY (link_id);


--
-- Name: activity_logbook_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_activity_logbook
    ADD CONSTRAINT activity_logbook_pkey PRIMARY KEY (log_id);


--
-- Name: activity_mitglied_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_activity_seeker
    ADD CONSTRAINT activity_mitglied_pkey PRIMARY KEY (link_id);


--
-- Name: activity_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_activity
    ADD CONSTRAINT activity_pkey PRIMARY KEY (activity_id);


--
-- Name: beruf_berufsbezeichnung_key; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_stuff_type
    ADD CONSTRAINT beruf_berufsbezeichnung_key UNIQUE (stuff_type);


--
-- Name: beruf_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_stuff_type
    ADD CONSTRAINT beruf_pkey PRIMARY KEY (stuff_id);


--
-- Name: bewerbung_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_request
    ADD CONSTRAINT bewerbung_pkey PRIMARY KEY (request_id);


--
-- Name: branchen_kat_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_industry
    ADD CONSTRAINT branchen_kat_pkey PRIMARY KEY (industry_id);


--
-- Name: common_container_name_key; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_common_container
    ADD CONSTRAINT common_container_name_key UNIQUE (name);


--
-- Name: common_container_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_common_container
    ADD CONSTRAINT common_container_pkey PRIMARY KEY (common_container_id);


--
-- Name: domain_name_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_provider_domain
    ADD CONSTRAINT domain_name_pkey PRIMARY KEY (domain_name);


--
-- Name: einschraenkung_merkmal_key; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_handicap
    ADD CONSTRAINT einschraenkung_merkmal_key UNIQUE (handicap_type);


--
-- Name: einschraenkung_mitglied_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_seeker_link_to_handicap
    ADD CONSTRAINT einschraenkung_mitglied_pkey PRIMARY KEY (seeker_handicap_id);


--
-- Name: einschraenkung_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_handicap
    ADD CONSTRAINT einschraenkung_pkey PRIMARY KEY (handicap_id);


--
-- Name: einschraenkung_stellen_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_offer_link_to_handicap
    ADD CONSTRAINT einschraenkung_stellen_pkey PRIMARY KEY (offer_handicap_id);


--
-- Name: email_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_provider_member_email
    ADD CONSTRAINT email_pkey PRIMARY KEY (email_id);


--
-- Name: filestore_container_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_filestore_container
    ADD CONSTRAINT filestore_container_pkey PRIMARY KEY (filestore_container_id);


--
-- Name: filestore_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_filestore
    ADD CONSTRAINT filestore_pkey PRIMARY KEY (file_id);


--
-- Name: firma_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_provider
    ADD CONSTRAINT firma_pkey PRIMARY KEY (provider_id);


--
-- Name: firmen_black_list_firmen_id_key; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_provider_black_list
    ADD CONSTRAINT firmen_black_list_firmen_id_key UNIQUE (provider_id);


--
-- Name: firmen_black_list_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_provider_black_list
    ADD CONSTRAINT firmen_black_list_pkey PRIMARY KEY (provider_black_list_id);


--
-- Name: firmen_mitarbeiter_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_provider_member
    ADD CONSTRAINT firmen_mitarbeiter_pkey PRIMARY KEY (member_id);


--
-- Name: firmen_mitarbeiter_tel_nr_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_provider_member_phone
    ADD CONSTRAINT firmen_mitarbeiter_tel_nr_pkey PRIMARY KEY (phone_id);


--
-- Name: game_funk_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY game_funk
    ADD CONSTRAINT game_funk_pkey PRIMARY KEY (nachrichten_id);


--
-- Name: game_landkarte_objekt_name_key; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY game_landkarte
    ADD CONSTRAINT game_landkarte_objekt_name_key UNIQUE (objekt_name);


--
-- Name: game_spieler_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY game_spieler
    ADD CONSTRAINT game_spieler_pkey PRIMARY KEY (mitglieds_id);


--
-- Name: game_werte_bezeichner_key; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY game_werte
    ADD CONSTRAINT game_werte_bezeichner_key UNIQUE (bezeichner);


--
-- Name: global_conf_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_global_conf
    ADD CONSTRAINT global_conf_pkey PRIMARY KEY (conf_id);


--
-- Name: mitglied_mitglieds_nr_key; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_seeker
    ADD CONSTRAINT mitglied_mitglieds_nr_key UNIQUE (seeker_no);


--
-- Name: mitglied_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_seeker
    ADD CONSTRAINT mitglied_pkey PRIMARY KEY (seeker_id);


--
-- Name: mitgliederberufe_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_seeker_link_to_stuff
    ADD CONSTRAINT mitgliederberufe_pkey PRIMARY KEY (seeker_stuff_id);


--
-- Name: mitglieds_tel_nr_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_seeker_phone
    ADD CONSTRAINT mitglieds_tel_nr_pkey PRIMARY KEY (phone_id);


--
-- Name: postfach_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_provider_pobox
    ADD CONSTRAINT postfach_pkey PRIMARY KEY (pobox_no);


--
-- Name: qualitaeten_merkmal_key; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_quality
    ADD CONSTRAINT qualitaeten_merkmal_key UNIQUE (quality_type);


--
-- Name: qualitaeten_mitglied_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_seeker_link_to_quality
    ADD CONSTRAINT qualitaeten_mitglied_pkey PRIMARY KEY (seeker_quality_id);


--
-- Name: qualitaeten_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_quality
    ADD CONSTRAINT qualitaeten_pkey PRIMARY KEY (quality_id);


--
-- Name: qualitaeten_stelle_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_offer_link_to_quality
    ADD CONSTRAINT qualitaeten_stelle_pkey PRIMARY KEY (offer_quality_id);


--
-- Name: stelle_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_offer
    ADD CONSTRAINT stelle_pkey PRIMARY KEY (offer_id);


--
-- Name: stellen_berufe_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace:
--

ALTER TABLE ONLY a23_offer_link_to_stuff
    ADD CONSTRAINT stellen_berufe_pkey PRIMARY KEY (offer_stuff_id);


--
-- Name: a23_activity_alarm_time_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_activity_alarm_time_index ON a23_activity USING btree (alarm_time);


--
-- Name: a23_activity_logbook_activity_id_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_activity_logbook_activity_id_index ON a23_activity_logbook USING btree (activity_id);


--
-- Name: a23_activity_priority_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_activity_priority_index ON a23_activity USING btree (priority);


--
-- Name: a23_activity_time_pressure_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_activity_time_pressure_index ON a23_activity USING btree (time_pressure);


--
-- Name: a23_filestore_container_file_id_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_filestore_container_file_id_index ON a23_filestore_container USING btree (file_id);


--
-- Name: a23_filestore_container_tag_id_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_filestore_container_tag_id_index ON a23_filestore_container USING btree (tag_id);


--
-- Name: a23_filestore_delete_date_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_filestore_delete_date_index ON a23_filestore USING btree (delete_date);


--
-- Name: a23_filestore_md5_sum_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_filestore_md5_sum_index ON a23_filestore USING btree (md5_sum);


--
-- Name: a23_newsletter_log_date_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_newsletter_log_date_index ON a23_newsletter_log USING btree (create_date);


--
-- Name: a23_newsletter_log_newsletter_id_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_newsletter_log_newsletter_id_index ON a23_newsletter_log USING btree (newsletter_id);


--
-- Name: a23_newsletter_sent_to_seeker_seeker_id_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_newsletter_sent_to_seeker_seeker_id_index ON a23_newsletter_log USING btree (newsletter_id);


--
-- Name: a23_provider_black_list_provider_id_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_provider_black_list_provider_id_index ON a23_provider_black_list USING btree (provider_id);


--
-- Name: a23_provider_member_provider_id_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_provider_member_provider_id_index ON a23_provider_member USING btree (provider_id);


--
-- Name: a23_provider_phone_provider_no_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_provider_phone_provider_no_index ON a23_provider_phone USING btree (phone_no);


--
-- Name: a23_provider_provider_id_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_provider_provider_id_index ON a23_provider USING btree (provider_id);


--
-- Name: a23_request_offer_id_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_request_offer_id_index ON a23_request USING btree (offer_id);


--
-- Name: a23_request_seeker_id_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_request_seeker_id_index ON a23_request USING btree (seeker_id);


--
-- Name: a23_seeker_link_to_handicap_handicap_id_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_seeker_link_to_handicap_handicap_id_index ON a23_seeker_link_to_handicap USING btree (handicap_id);


--
-- Name: a23_seeker_link_to_handicap_seeker_id_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_seeker_link_to_handicap_seeker_id_index ON a23_seeker_link_to_handicap USING btree (seeker_id);


--
-- Name: a23_seeker_link_to_quality_quality_id_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_seeker_link_to_quality_quality_id_index ON a23_seeker_link_to_quality USING btree (quality_id);


--
-- Name: a23_seeker_link_to_quality_seeker_id_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_seeker_link_to_quality_seeker_id_index ON a23_seeker_link_to_quality USING btree (seeker_id);


--
-- Name: a23_seeker_link_to_stuff_seeker_id_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_seeker_link_to_stuff_seeker_id_index ON a23_seeker_link_to_stuff USING btree (seeker_id);


--
-- Name: a23_seeker_link_to_stuff_stuff_id_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_seeker_link_to_stuff_stuff_id_index ON a23_seeker_link_to_stuff USING btree (stuff_id);


--
-- Name: a23_seeker_logbook_mitglied_log_id_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_seeker_logbook_mitglied_log_id_index ON a23_seeker_logbook USING btree (seeker_id);


--
-- Name: a23_seeker_seeker_id_index; Type: INDEX; Schema: public; Owner: -; Tablespace:
--

CREATE INDEX a23_seeker_seeker_id_index ON a23_seeker USING btree (seeker_id);


--
-- Name: a23_file_reserve_file_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_file_reserve
    ADD CONSTRAINT a23_file_reserve_file_id_fkey FOREIGN KEY (file_id) REFERENCES a23_filestore(file_id);


--
-- Name: a23_file_reserve_mitglieds_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_file_reserve
    ADD CONSTRAINT a23_file_reserve_mitglieds_id_fkey FOREIGN KEY (editor_id) REFERENCES a23_seeker(seeker_id);


--
-- Name: a23_newsletter_log_crm_user_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_newsletter_log
    ADD CONSTRAINT a23_newsletter_log_crm_user_id_fkey FOREIGN KEY (editor_id) REFERENCES a23_seeker(seeker_id);


--
-- Name: a23_newsletter_sent_to_seeker_crm_user_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_newsletter_sent_to_seeker
    ADD CONSTRAINT a23_newsletter_sent_to_seeker_crm_user_id_fkey FOREIGN KEY (seeker_id) REFERENCES a23_seeker(seeker_id);


--
-- Name: a23_newsletter_sent_to_seeker_newsletter_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_newsletter_sent_to_seeker
    ADD CONSTRAINT a23_newsletter_sent_to_seeker_newsletter_id_fkey FOREIGN KEY (newsletter_id) REFERENCES a23_newsletter_log(newsletter_id);


--
-- Name: a23_provider_filestore_filestore_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_provider_filestore
    ADD CONSTRAINT a23_provider_filestore_filestore_id_fkey FOREIGN KEY (filestore_id) REFERENCES a23_filestore(file_id);


--
-- Name: a23_provider_filestore_provider_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_provider_filestore
    ADD CONSTRAINT a23_provider_filestore_provider_id_fkey FOREIGN KEY (provider_id) REFERENCES a23_provider(provider_id);


--
-- Name: a23_seeker_filestore_filestore_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_seeker_filestore
    ADD CONSTRAINT a23_seeker_filestore_filestore_id_fkey FOREIGN KEY (filestore_id) REFERENCES a23_filestore(file_id);


--
-- Name: a23_seeker_filestore_seeker_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_seeker_filestore
    ADD CONSTRAINT a23_seeker_filestore_seeker_id_fkey FOREIGN KEY (seeker_id) REFERENCES a23_seeker(seeker_id);


--
-- Name: a23_seeker_logbook_autor_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_seeker_logbook
    ADD CONSTRAINT a23_seeker_logbook_autor_id_fkey FOREIGN KEY (editor_id) REFERENCES a23_seeker(seeker_id);


--
-- Name: a23_seeker_logbook_mitglied_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_seeker_logbook
    ADD CONSTRAINT a23_seeker_logbook_mitglied_id_fkey FOREIGN KEY (seeker_id) REFERENCES a23_seeker(seeker_id);


--
-- Name: activity_activity_aim_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_activity_activity
    ADD CONSTRAINT activity_activity_aim_id_fkey FOREIGN KEY (aim_id) REFERENCES a23_activity(activity_id);


--
-- Name: activity_activity_owner_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_activity_activity
    ADD CONSTRAINT activity_activity_owner_id_fkey FOREIGN KEY (owner_id) REFERENCES a23_activity(activity_id);


--
-- Name: activity_container_activity_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_activity_container
    ADD CONSTRAINT activity_container_activity_id_fkey FOREIGN KEY (activity_id) REFERENCES a23_activity(activity_id);


--
-- Name: activity_container_container_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_activity_container
    ADD CONSTRAINT activity_container_container_id_fkey FOREIGN KEY (container_id) REFERENCES a23_common_container(common_container_id);


--
-- Name: activity_filestore_activity_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_activity_filestore
    ADD CONSTRAINT activity_filestore_activity_id_fkey FOREIGN KEY (activity_id) REFERENCES a23_activity(activity_id);


--
-- Name: activity_filestore_filestore_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_activity_filestore
    ADD CONSTRAINT activity_filestore_filestore_id_fkey FOREIGN KEY (filestore_id) REFERENCES a23_filestore(file_id);


--
-- Name: activity_firma_activity_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_activity_provider
    ADD CONSTRAINT activity_firma_activity_id_fkey FOREIGN KEY (activity_id) REFERENCES a23_activity(activity_id);


--
-- Name: activity_firma_firma_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_activity_provider
    ADD CONSTRAINT activity_firma_firma_id_fkey FOREIGN KEY (provider_id) REFERENCES a23_provider(provider_id);


--
-- Name: activity_logbook_activity_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_activity_logbook
    ADD CONSTRAINT activity_logbook_activity_id_fkey FOREIGN KEY (activity_id) REFERENCES a23_activity(activity_id);


--
-- Name: activity_logbook_autor_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_activity_logbook
    ADD CONSTRAINT activity_logbook_autor_id_fkey FOREIGN KEY (editor_id) REFERENCES a23_seeker(seeker_id);


--
-- Name: activity_mitglied_activity_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_activity_seeker
    ADD CONSTRAINT activity_mitglied_activity_id_fkey FOREIGN KEY (activity_id) REFERENCES a23_activity(activity_id);


--
-- Name: activity_mitglied_mitglieds_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_activity_seeker
    ADD CONSTRAINT activity_mitglied_mitglieds_id_fkey FOREIGN KEY (seeker_id) REFERENCES a23_seeker(seeker_id);


--
-- Name: bewerbung_mitglieds_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_request
    ADD CONSTRAINT bewerbung_mitglieds_id_fkey FOREIGN KEY (seeker_id) REFERENCES a23_seeker(seeker_id);


--
-- Name: bewerbung_stellen_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_request
    ADD CONSTRAINT bewerbung_stellen_id_fkey FOREIGN KEY (offer_id) REFERENCES a23_offer(offer_id);


--
-- Name: bewerbung_vorgangs_bearbeiter_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_request
    ADD CONSTRAINT bewerbung_vorgangs_bearbeiter_fkey FOREIGN KEY (editor_id) REFERENCES a23_seeker(seeker_id);


--
-- Name: branchen_kat_firmen_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_industry
    ADD CONSTRAINT branchen_kat_firmen_id_fkey FOREIGN KEY (provider_id) REFERENCES a23_provider(provider_id);


--
-- Name: domain_name_firmen_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_provider_domain
    ADD CONSTRAINT domain_name_firmen_id_fkey FOREIGN KEY (provider_id) REFERENCES a23_provider(provider_id);


--
-- Name: einschraenkung_mitglied_merkmal_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_seeker_link_to_handicap
    ADD CONSTRAINT einschraenkung_mitglied_merkmal_id_fkey FOREIGN KEY (handicap_id) REFERENCES a23_handicap(handicap_id);


--
-- Name: einschraenkung_mitglied_mitglieds_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_seeker_link_to_handicap
    ADD CONSTRAINT einschraenkung_mitglied_mitglieds_id_fkey FOREIGN KEY (seeker_id) REFERENCES a23_seeker(seeker_id);


--
-- Name: einschraenkung_stellen_merkmal_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_offer_link_to_handicap
    ADD CONSTRAINT einschraenkung_stellen_merkmal_id_fkey FOREIGN KEY (handicap_id) REFERENCES a23_handicap(handicap_id);


--
-- Name: einschraenkung_stellen_stellen_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_offer_link_to_handicap
    ADD CONSTRAINT einschraenkung_stellen_stellen_id_fkey FOREIGN KEY (offer_id) REFERENCES a23_offer(offer_id);


--
-- Name: email_firmen_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_provider_member_email
    ADD CONSTRAINT email_firmen_id_fkey FOREIGN KEY (provider_id) REFERENCES a23_provider(provider_id);


--
-- Name: email_mitarbeiter_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_provider_member_email
    ADD CONSTRAINT email_mitarbeiter_id_fkey FOREIGN KEY (member_id) REFERENCES a23_provider_member(member_id);


--
-- Name: filestore_container_file_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_filestore_container
    ADD CONSTRAINT filestore_container_file_id_fkey FOREIGN KEY (file_id) REFERENCES a23_filestore(file_id);


--
-- Name: filestore_container_tag_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_filestore_container
    ADD CONSTRAINT filestore_container_tag_id_fkey FOREIGN KEY (tag_id) REFERENCES a23_common_container(common_container_id);


--
-- Name: filestore_version_of_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_filestore
    ADD CONSTRAINT filestore_version_of_id_fkey FOREIGN KEY (version_of_id) REFERENCES a23_filestore(file_id);


--
-- Name: firma_mutterkonzern_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_provider
    ADD CONSTRAINT firma_mutterkonzern_fkey FOREIGN KEY (parent_company) REFERENCES a23_provider(provider_id);


--
-- Name: firmen_black_list_firmen_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_provider_black_list
    ADD CONSTRAINT firmen_black_list_firmen_id_fkey FOREIGN KEY (provider_id) REFERENCES a23_provider(provider_id);


--
-- Name: firmen_mitarbeiter_firmen_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_provider_member
    ADD CONSTRAINT firmen_mitarbeiter_firmen_id_fkey FOREIGN KEY (provider_id) REFERENCES a23_provider(provider_id);


--
-- Name: firmen_mitarbeiter_tel_nr_firmen_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_provider_member_phone
    ADD CONSTRAINT firmen_mitarbeiter_tel_nr_firmen_id_fkey FOREIGN KEY (member_id) REFERENCES a23_provider_member(member_id);


--
-- Name: firmen_nummer_firmen_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_provider_phone
    ADD CONSTRAINT firmen_nummer_firmen_id_fkey FOREIGN KEY (provider_id) REFERENCES a23_provider(provider_id);


--
-- Name: game_spieler_mitglieds_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY game_spieler
    ADD CONSTRAINT game_spieler_mitglieds_id_fkey FOREIGN KEY (mitglieds_id) REFERENCES a23_seeker(seeker_id);


--
-- Name: mitgliederberufe_berufs_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_seeker_link_to_stuff
    ADD CONSTRAINT mitgliederberufe_berufs_id_fkey FOREIGN KEY (stuff_id) REFERENCES a23_stuff_type(stuff_id);


--
-- Name: mitgliederberufe_mitglieds_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_seeker_link_to_stuff
    ADD CONSTRAINT mitgliederberufe_mitglieds_id_fkey FOREIGN KEY (seeker_id) REFERENCES a23_seeker(seeker_id);


--
-- Name: mitglieds_tel_nr_mitglieds_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_seeker_phone
    ADD CONSTRAINT mitglieds_tel_nr_mitglieds_id_fkey FOREIGN KEY (seeker_id) REFERENCES a23_seeker(seeker_id);


--
-- Name: postfach_firmen_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_provider_pobox
    ADD CONSTRAINT postfach_firmen_id_fkey FOREIGN KEY (provider_id) REFERENCES a23_provider(provider_id);


--
-- Name: qualitaeten_mitglied_merkmal_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_seeker_link_to_quality
    ADD CONSTRAINT qualitaeten_mitglied_merkmal_id_fkey FOREIGN KEY (quality_id) REFERENCES a23_quality(quality_id);


--
-- Name: qualitaeten_mitglied_mitglieds_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_seeker_link_to_quality
    ADD CONSTRAINT qualitaeten_mitglied_mitglieds_id_fkey FOREIGN KEY (seeker_id) REFERENCES a23_seeker(seeker_id);


--
-- Name: qualitaeten_stelle_merkmal_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_offer_link_to_quality
    ADD CONSTRAINT qualitaeten_stelle_merkmal_id_fkey FOREIGN KEY (quality_id) REFERENCES a23_quality(quality_id);


--
-- Name: qualitaeten_stelle_stellen_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_offer_link_to_quality
    ADD CONSTRAINT qualitaeten_stelle_stellen_id_fkey FOREIGN KEY (offer_id) REFERENCES a23_offer(offer_id);


--
-- Name: stelle_firmen_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_offer
    ADD CONSTRAINT stelle_firmen_id_fkey FOREIGN KEY (provider_id) REFERENCES a23_provider(provider_id);


--
-- Name: stellen_berufe_stellen_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY a23_offer_link_to_stuff
    ADD CONSTRAINT stellen_berufe_stellen_id_fkey FOREIGN KEY (offer_id) REFERENCES a23_offer(offer_id);


--
-- Name: public; Type: ACL; Schema: -; Owner: -
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--

