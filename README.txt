

ABHÄNGIGKEITEN
--------------

gcc-g++
tntnet
tntnet-devel
cxxtools
cxxtools-devel
libpqxx-devel 
libpqxx
openssl-devel


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
createuser -W artikel23_user
# Datenbank erstellen und User zuweisen
createdb -O artikel23_user  artikel23t_db
# ggf. Anpassungen an der Konfiguration in
/var/lib/pgsql/data/pg_hba.conf 
# Server neu starten
systemctl restart postgresql.service
# Verbindung testen
psql -U artikel23_user -h localhost -W artikel23t_db
# Log-Analyse:
 tail -n 60 /var/lib/pgsql/data/pg_log/postgresql-Sun.log