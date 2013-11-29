# norootforbuild
BuildRequires: qt-devel

#%if 0%{?centos_version}<=5
#define qmake /usr/bin/qmake-qt4
#BuildRequires: qt4-phonon-devel 
#Requires:qt47-sqlite,libphonon
#%endif

%if 0%{?centos_version}>=6 
%define qmake /usr/bin/qmake-qt4
   %define qmake /usr/bin/qmake-qt4
   
BuildRequires:	qt-devel
BuildRequires:  phonon-devel

%endif

%if 0%{?suse_version}
     %define qmake /usr/bin/qmake
BuildRequires:	libqt4-devel
BuildRequires:  phonon-devel
Requires: libqt4-x11 >= 4.6.2

%endif

%if 0%{?fedora_version} || 0%{?rhel_version}
   %define qmake /usr/bin/qmake-qt4   
BuildRequires:	qt-devel
BuildRequires:  phonon-devel

%endif


%if 0%{?mandriva_version}  || 0%{?mdkversion}
      %define qmake /usr/lib/qt4/bin/qmake
BuildRequires: phonon-devel

%endif


Name:	%{name}
Version:	1.0
Release:	0.0
License:	GPL3
Group:	Settings/DesktopSettings
Summary:	%{name} the the gui for xwinwrap
URL:	http://elkirtasse.22web.net/

Source0:	%{name}_%{version}.tar.gz

BuildRoot:	%{_tmppath}/%{name}-%{version}-build

BuildRequires:	gcc-c++





%description
برنامج qwinwrap.
 يتيح لك هذا البرنامج تغيير خلفية سطح المكتب الى شاشة توقف اوفيديو.
 باستخدام برنامج xwinwrap .
 او باستخدام الرسم المباشر على سطح المكتب.

%prep
%setup -q -n %{name}-%{version}

%build
%{qmake}

make

%install
# binary
%{makeinstall} INSTALL_ROOT=%{buildroot}
%clean
%{__rm} -rf %{buildroot}


%files
%defattr(-,root,root,-)
%{_bindir}
%{_bindir}/%{name}
%{_datadir}
%{_datadir}/applications
%{_datadir}/applications/%{name}.desktop

%{_datadir}/icons
%{_datadir}/icons/hicolor
%{_datadir}/icons/hicolor/64x64
%{_datadir}/icons/hicolor/64x64/apps
%{_datadir}/icons/hicolor/64x64/apps/%{name}.png

%changelog


