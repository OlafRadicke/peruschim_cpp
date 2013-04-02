

ABHÄNGIGKEITEN
--------------

gcc-g++
tntnet
tntnet-devel
cxxtools
cxxtools-devel
libpqxx-devel 
libpqxx


INSTALLATION
------------


DATENBANK VORBEREITEN

(unter Fedora 17)
# Server installieren
yum -y install postgresql-server
# Datenbank initalisieren
service postgresql initdb
# Server starten
systemctl start postgresql.service
# Einstellen das nach Systemstart Datenbank automatisch startet.
chkconfig postgresql on
# Zum postgres-Accound wechseln
su - postgres
# Neuen Datenbank-User anlegen
createuser -W peruschim_cpp
# Datenbank erstellen und User zuweisen
createdb -O peruschim_cpp  peruschim_cpp
# ggf. Anpassungen an der Konfiguration in
/var/lib/pgsql/data/pg_hba.conf 
# Server neu starten
systemctl restart postgresql.service
# Verbindung testen
psql -U peruschim_cpp -h localhost -W peruschim_cpp
# Log-Analyse:
 tail -n 60 /var/lib/pgsql/data/pg_log/postgresql-Sun.log
# Tabellen erstellen:
psql -h localhost -U peruschim_cpp peruschim_cpp < /peruschim_cpp/PostgreSQL/db_schema.sql


STARTEN
-------

tntnet ./tntnet.conf
