Name: peruschim_cpp
Summary: Web based bible tool.
Version: 1
Group: Web-Applications
License: AGPL
Release: 1
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-olaf-%(%{__id_u} -n)
BuildArch:
Requires: tntnet
Source: peruschim_cpp-%{version}.tar.gz

%description
Ein Tool um Bibel-Verse-Stellen zu sammeln und mit anderen zu teilen.

%prep
%setup

%build
./configure
make

%install
if [ ! -d $RPM_BUILD_ROOT/usr/bin/peruschim_cpp/ ] ; \
then  mkdir -p $RPM_BUILD_ROOT/usr/bin/peruschim_cpp/ ; fi;

install  $RPM_BUILD_DIR/peruschim_cpp-%{version}/src/peruschim_cpp  \
    $RPM_BUILD_ROOT/usr/bin/peruschim_cpp/
install  $RPM_BUILD_DIR/peruschim_cpp-%{version}/exsamples/peruschim_cpp.conf \
    $RPM_BUILD_ROOT/usr/bin/peruschim_cpp/peruschim_cpp.conf.exsample


%prep
%setup
