INCLUDES = -I$(top_srcdir) -I$(includedir) \
	  -DG_LOG_DOMAIN=\"pwman\" 
		
bin_PROGRAMS = pwman convert_pwdb pwdb2csv

pwman_SOURCES = options.c pwlist.c ui.c uilist.c pwman.c actions.c launch.c ui.h \
		pwman.h help.h filter.c gnupg.c pwgen.c misc.c 

convert_pwdb_SOURCES = convert_pwdb.c

pwdb2csv_SOURCES = pwdb2csv.c
