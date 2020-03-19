
randlibhw.o: randlibhw.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

randlibsw.o: randlibsw.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

randcpuid.o: randcpuid.c
	$(CC) $(CFLAGS) -c $< -o $@

randmain.o: randmain.c
	$(CC) $(CFLAGS) -c $< -o $@

librandcpuid.a: randcpuid.o
	ar rcs randcpuid_static.a $<

randlibsw.so: randlibsw.o
	$(CC) $(CFLAGS) -shared -o $@ $<

randlibhw.so: randlibhw.o
	$(CC) $(CFLAGS) -shared -o $@ $<

randmain: randcpuid.o randmain.o
	$(CC) $(CFLAGS) -ldl -Wl,-rpath=$(PWD) $^ -o $@

