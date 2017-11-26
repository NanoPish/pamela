CC = gcc
CFLAGS = -fPIC -W -Wall -Wextra -O2
TESTFLAGS = -W -Wall -Wextra -pthread -lcheck_pic -pthread -lrt -lm -lsubunit -lcheck
LDFLAGS = -shared

RM = rm -f

TARGET_LIB = pamela_module.so

SRCS = pamela_module.c pamela_utility.c pamela_container.c
OBJS = $(SRCS:.c=.o)
TESTS = pamela_utility

PREFIX = /lib

all: 		${TARGET_LIB}

$(TARGET_LIB): 	$(OBJS)
		$(CC) ${LDFLAGS} -o $@ $^

clean:
		${RM} ${TARGET_LIB} ${TESTS} ${OBJS} ${TESTS}-test.c

re:		clean all

install:	$(TARGET_LIB)
		mkdir -p $(PREFIX)/security/
	    	$(RM) $(PREFIX)/security/$<
	    	cp $< $(PREFIX)/security/
		if ! grep -q pamela_module.so /etc/pam.d/common-session; then \
			 echo "session optional pamela_module.so" >> /etc/pam.d/common-session; \
		fi

uninstall:
		$(RM) $(PREFIX)/security/$(TARGET_LIB)
		if grep -q pamela_module.so /etc/pam.d/common-session; then \
			sed -i '/pamela_module.so/d' /etc/pam.d/common-session; \
		fi

check:
		if [ -f /etc/pam.d/common-session ] && grep -q pamela_module.so /etc/pam.d/common-session; then \
			echo "PAMELA PAM MODULE IS CORRECTLY INSTALLED AND CONFIGURED !"; \
		else \
			echo "PAMELA PAM MODULE IS NOT INSTALLED OR NOT CONFIGURED !"; \
		fi

test:
		@for t in $(TESTS); do \
			checkmk $$t-test.check > $$t-test.c; \
			$(CC) -o $$t $$t.c $$t-test.c $(TESTFLAGS); \
			./$$t; \
		done \

.PHONY:		clean all re install uninstall test check
