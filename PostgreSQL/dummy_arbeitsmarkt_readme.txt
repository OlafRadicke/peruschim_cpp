ENGLISH (DEUTSCH weiter unten)

Short description:
------------------
This is only a little sample database called 'dummy' for
beginners to have something to play with.
The theme used is 'job market' (Gernan Arbeitsmarkt)
including some sample data - job seekers, offers, activities,
inustries, ...

How to use:
-----------
To use it, you have to create a role (i.e. one named 'dummy'
and with the password 'dummy') and a database (with the same
name 'dummy') (i.e. using PgAdmin III).

If you already use a database named 'dummy', you can delete
(drop) it with following command in the PostgreSQL console:
dropdb dummy

You will create the database in the same console using this
command:
createdb -O db_name -h db_ip -p db_port -U user_name -W user_password
Example:
createdb -O dummy -h 127.0.0.1 -p 5432 -U dummy -W dummy
Password: dummy

To import the tables and their data open the PostgreSQL
console and paste or type in following command:
psql -U psql_user_name -d db_name -f path_to_this_sql_dump_file
Example:
psql -U postgres -d dummy -f c:\path_to_this_sql_dump_file\dummy_arbeitsmarkt.sql

If you're done, copy the sample configuration 'artikel23.conf'
into your artikel23 program folder and start artikel23.exe.

Backup samples:
Linux:
pg_dump artikel_23 > dummy_arbeitsmarkt_bak.sql

Windows:
pg_dump -C -d -U dummy dummy > c:\path_to_this_sql_dump_file\dummy_arbeitsmarkt_bak.sql

-------------------------------------------------------

DEUTSCH

Kurzbeschreibung:
-----------------
Dies ist nur eine kleine Beispieldatenbank namens 'dummy',
damit Anfänger etwas zum Spielen haben.
Das verwendete Theme ist 'Arbeitsmarkt' und es enthält
einige Beispieldaten - Bewerber, Stellen, Aktivitäten,
Branchen, ...

Anwendung:
----------
Um sie zu nutzen, muss zuerst eine Rolle (z. B. eine namens
'dummy' und mit dem Passwort 'dummy') und eine Datenbank
(mit gleichem Namen 'dummy') angelegt werden (z. B. mit
PgAdmin III).

Sollten Sie bereits eine Datenbank namens 'dummy' nutzen,
können Sie diese mit folgendem Befehl in der PostgreSQL-Konsole
löschen (droppen):
dropdb dummy

Die Datenbank erstellen Sie ebenso in dieser Konsole über den
Befehl:
createdb -O db_user_name -h db_ip -p db_port -U user_name -W user_password
Beispiel:
createdb -O dummy -h 127.0.0.1 -p 5432 -U dummy -W dummy
Passwort: dummy

Um die Tabellen und ihre Daten zu importieren, öffnen Sie die
PostgreSQL-Konsole und fügen Sie folgenden Befehl ein:
psql -U psql_user_name -d db_name -f path_to_this_sql_dump_file
Beispiel:
psql -U postgres -d dummy -f c:\path_to_this_sql_dump_file\dummy_arbeitsmarkt.sql

Sind Sie damit fertig, kopieren Sie die Beispielkonfiguration
'artikel23.conf' in Ihren artikel23-Programmordner und starten
artikel23.exe.

Backup-Beispiele:
Linux:
pg_dump artikel_23 > dummy_arbeitsmarkt_bak.sql

Windows:
pg_dump -C -d -U dummy dummy > c:\path_to_this_sql_dump_file\dummy_arbeitsmarkt_bak.sql
