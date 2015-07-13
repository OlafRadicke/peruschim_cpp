Name: peruschim_cpp
Summary: Web based bible tool.
Version: 2
Group: Web-Applications
License: AGPL
Release: 1
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-olaf-%(%{__id_u} -n)
# Requires: tntnet
BuildRequires: autoconf
Source: peruschim_cpp-%{version}.tar.gz

%description
Ein Tool um Bibel-Verse-Stellen zu sammeln und mit anderen zu teilen.

#%prep
#%setup

%build

%install

wget https://github.com/OlafRadicke/peruschim_cpp/archive/master.zip
ls -lah %{_builddir}/
cd %{_builddir}
unzip -u master.zip
ls -lah %{_builddir}/
cd %{_builddir}/peruschim_cpp-master
/usr/bin/ls -lah
autoreconf -i
./configure --help
/bin/bash ./configure
make
ls -lah


mkdir -p $RPM_BUILD_ROOT/usr/bin/peruschim_cpp/

install  $RPM_BUILD_DIR/peruschim_cpp-%{version}/src/peruschim_cpp  \
    $RPM_BUILD_ROOT/usr/bin/peruschim_cpp/
install  $RPM_BUILD_DIR/peruschim_cpp-%{version}/exsamples/peruschim_cpp.conf \
    $RPM_BUILD_ROOT/usr/bin/peruschim_cpp/peruschim_cpp.conf.exsample

%clean
rm -rf $RPM_BUILD_ROOT

%files
%dir %attr(770, root, root) /usr/bin/peruschim_cpp/
%attr(775, root, root) /usr/bin/peruschim_cpp/peruschim_cpp
%attr(774, root, root) /usr/bin/peruschim_cpp/peruschim_cpp.conf.exsample


%changelog
* Mon Jul 13 2015 Olaf Radicke <briefkasten@olaf-radicke.de> - 2.1
- RPM zieht sich die Sourcen für den Bau selber.
* Fri Aug  2 2013 Olaf Radicke <briefkasten@olaf-radicke.de> - 1.1
- Erste version.
