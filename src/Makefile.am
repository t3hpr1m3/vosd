SUBDIRS = ./alsa

bin_PROGRAMS = vosd

vosd_CPPFLAGS = $(ALSA_CFLAGS) $(LIBXOSD_CFLAGS)
vosd_LDFLAGS = $(ALSA_LIBS) $(LIBXOSD_LIBS)
vosd_LDADD = alsa/libalsa.a

vosd_SOURCES = log.cpp main.cpp

