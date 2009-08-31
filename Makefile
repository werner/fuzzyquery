MODULE_big = fuzzyquery
OBJS= gram.o parsing.o fuzzyquery.o
DATA_built = $(addsuffix .sql, $(MODULE_big))

subdir = contrib/fuzzyquery
top_builddir = ../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk

FLEXFLAGS = -CF

# scan is compiled as part of gram
gram.o: $(srcdir)/scan.c

$(srcdir)/gram.h: $(srcdir)/gram.c ;

$(srcdir)/gram.c: gram.y
ifdef BISON
	$(BISON) -d $(BISONFLAGS) -o $@ $<
else
	@$(missing) bison $< $@
endif

$(srcdir)/scan.c: scan.l
ifdef FLEX
	$(FLEX) $(FLEXFLAGS) -o'$@' $<
else
	@$(missing) flex $< $@
endif

scan.o gram.o parsing.o parser.o: $(srcdir)/gram.h

distprep: $(srcdir)/gram.c $(srcdir)/scan.c

clean:
	rm -f $(srcdir)/gram.c $(srcdir)/scan.c *~ gram.h gram.output *.o
