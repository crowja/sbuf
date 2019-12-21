SHELL = /bin/sh

GCC_STRICT_FLAGS = -pedantic -ansi -std=c89 -W -Wall -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -O2
GCC_SANITIZE_FLAGS = -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
OTHER_SOURCE =
OTHER_INCLUDE = -I.
CPPFLAGS = -I. $(OTHER_INCLUDE)
CFLAGS = $(GCC_STRICT_FLAGS) 
LDFLAGS =
LDFLAGS_EFENCE = -L/usr/local/lib -lefence $(LDFLAGS)
#VALGRIND_FLAGS = --verbose --leak-check=full --undef-value-errors=yes --track-origins=yes
VALGRIND_FLAGS =  --leak-check=summary --undef-value-errors=yes --track-origins=yes

INDENT_FLAGS = -TFILE -Tsize_t -Tuint8_t -Tuint16_t -Tuint32_t -Tuint64_t

.PHONY: check check-examples vcheck scheck echeck indent stamp clean

TESTS     = t/test
EXAMPLES  = ex/ex_1 ex/ex_2 ex/ex_3

sbuf.o: sbuf.c sbuf.h
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ sbuf.c

check:
	@for i in $(TESTS); \
	do \
	  echo "--------------------"; \
	  echo "Running test $$i ..."; \
	  ( $(CC)    $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o t/a.out $$i.c sbuf.c $(LDFLAGS) ) \
	  && ( t/a.out ); \
	done 

check-examples:
	echo "--------------------"; \
	echo "Running test ex/ex_1.c ..."; \
	( $(CC) -g $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o ex/a.out ex/ex_1.c sbuf.c $(LDFLAGS) ) \
	&& ( valgrind $(VALGRIND_FLAGS) ex/a.out ); \
	echo "Running test ex/ex_2.c ..."; \
	( $(CC) -g $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o ex/a.out ex/ex_2.c sbuf.c $(LDFLAGS) ) \
	&& ( valgrind $(VALGRIND_FLAGS) ex/a.out < NOTES.md ); \
	echo "Running test ex/ex_3.c ..."; \
	( $(CC) -g $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o ex/a.out ex/ex_3.c sbuf.c $(LDFLAGS) ) \
	&& ( valgrind $(VALGRIND_FLAGS) ex/a.out < NOTES.md ); \

vcheck:
	@for i in $(TESTS); \
	do \
	  echo "--------------------"; \
	  echo "Running test $$i ..."; \
	  ( $(CC) -g $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o t/a.out $$i.c sbuf.o $(LDFLAGS) ) \
	  && ( valgrind $(VALGRIND_FLAGS) t/a.out ); \
	done 

scheck:
	@for i in $(TESTS); \
	do \
	  echo "--------------------"; \
	  echo "Running test $$i ..."; \
	  ( $(CC)    $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(GCC_SANITIZE_FLAGS) $(OTHER_SOURCE) \
		-o t/a.out $$i.c sbuf.c $(LDFLAGS) ) \
	  && ( t/a.out ); \
	done 

echeck:
	@for i in $(TESTS); \
	do \
	  echo "--------------------"; \
	  echo "Running test $$i ..."; \
	  ( $(CC)    $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o t/a.out $$i.c sbuf.o $(LDFLAGS_EFENCE) ) \
	  && ( LD_PRELOAD=libefence.so ./t/a.out ); \
	done 

indent: stamp
	@indent $(INDENT_FLAGS) sbuf.c
	@indent $(INDENT_FLAGS) sbuf.h
	@indent $(INDENT_FLAGS) t/test.c
	@indent $(INDENT_FLAGS) ex/ex_1.c
	@indent $(INDENT_FLAGS) ex/ex_2.c
	@indent $(INDENT_FLAGS) ex/ex_3.c

stamp:
	@bash stamper.bash sbuf.c
	@bash stamper.bash sbuf.h

clean:
	@/bin/rm -f ./*.o ./*~ ./*.BAK ./*.bak ./core.* ./a.out
	@/bin/rm -f t/*.o t/*~ t/*.BAK t/*.bak t/core.* t/a.out
	@/bin/rm -f ex/*.o ex/*~ ex/*.BAK ex/*.bak ex/core.* ex/a.out
