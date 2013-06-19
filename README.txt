

ABHÄNGIGKEITEN
--------------

- gcc-g++
- tntnet
- tntnet-devel
- tntdb
zum übersetzen von Tntnet:
- automake
- autoconf
- libtool
- postgresql-devel
- zlib-devel
- openssl-devel

Peruschim benutzt PostgreSQL als Backend so das u.U.
"./configure --with-sqlite=no --with-mysql=no" beim übersetzen von tntdb
angegeben werden muss.


INSTALLATION
------------


DATENBANK VORBEREITEN

(unter Fedora 17)
# Server installieren
# Redhat, Fedora...
yum -y install postgresql-server
#Debian...
aptitude install  postgresql

# Datenbank initalisieren (Redhat/Fedora)
service postgresql initdb
# Server starten (Redhat/Fedora)
systemctl start postgresql.service
# Einstellen das nach Systemstart Datenbank automatisch startet. (Redhat/Fedora)
chkconfig postgresql on
# Zum postgres-Accound wechseln
su - postgres
# Neuen Datenbank-User anlegen
createuser -W peruschim_cpp
# Datenbank erstellen und User zuweisen
createdb -O peruschim_cpp  peruschim_cpp
# ggf. Anpassungen an der Konfiguration in
# Rdehat/Fedora
/var/lib/pgsql/data/pg_hba.conf
# Debian...
/etc/postgresql/9.1/main/pg_hba.conf

# Server neu starten
systemctl restart postgresql.service
# Verbindung testen
psql -U peruschim_cpp -h localhost -W peruschim_cpp
# Log-Analyse:
 tail -n 60 /var/lib/pgsql/data/pg_log/postgresql-Sun.log
# Tabellen erstellen:
psql -h localhost -U peruschim_cpp peruschim_cpp < /peruschim_cpp/PostgreSQL/db_schema.sql

PERUSCHIM ÜBERSETZEN

# Der Parameter "-j 4" ist optional und weist gnu make an, vier cores zu
# benutzen, bzw. 4 Jobs parallel auszuführen.
make -j 4


STARTEN
-------

nach dem Komplieren einfach die Datei ./peruschim_cp ausfüren.
Das initale Passwort von User "admin" ist "admin". Das Passwort
sollte sofort nach der Installation geändert werden.


TROUBLESHOOTING
---------------

Wenn beim starten eine solche Fehlermeldung kommt:

or@hamburg:~/a-z/g/git-repos/peruschim_cpp$ ./peruschim_cpp
    /peruschim_cpp: error while loading shared libraries: libtntdb.so.3: cannot
    open shared object file: No such file or directory

Ist dem System die shared libraries der libtntdb nicht bekannt. Stelle sicher
das Tntdb installiert ist und kontrolliere die Konfiguration in /etc/ld.so.conf.d/
ob der Pfad zur shared librarie konfiguriert ist. Wenn nicht lege eine
Konfigurationsdatei an mit den Namen /etc/ld.so.conf.d/tntdb.conf. Deren Inhalt
muss lauten:
/usr/local/lib/

Oder je nach dem wo deine Lib installiert ist. Danach muss die Konfiguration
vom System neu eingelesen werden. Das geschied mir dem Befehl: "ldconfig"

