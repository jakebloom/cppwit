CC=g++

IDIR=include
ODIR=bin
SRCDIR=src
CFLAGS=-Wall -Werror --std=c++14 -I $(IDIR)


%.o: $(SRCDIR)/%.cpp $(IDIR)/%.h
	mkdir -p $(ODIR)
	$(CC) -c -o $(ODIR)/$@ $< $(CFLAGS)

%.fpic.o: $(SRCDIR)/%.cpp $(IDIR)/%.h
	mkdir -p $(ODIR)
	$(CC) -c -o $(ODIR)/$@ $< $(CFLAGS) -fPIC

test: Wit.o WitResp.o
	mkdir -p $(ODIR)
	$(CC) -o $(ODIR)/test $(ODIR)/Wit.o $(ODIR)/WitResp.o $(SRCDIR)/test.cpp $(CFLAGS) -lcurl

static: Wit.o WitResp.o
	mkdir -p $(ODIR)
	ar rcs $(ODIR)/libWit.a $(ODIR)/Wit.o $(ODIR)/WitResp.o

dynamic: Wit.fpic.o WitResp.fpic.o
	mkdir -p $(ODIR)
	$(CC) -shared $(ODIR)/Wit.o $(ODIR)/WitResp.o -lcurl -o $(ODIR)/libWit.so
	cp $(ODIR)/libWit.so /usr/local/lib/libWit.so
	cp $(IDIR)/Wit.h /usr/local/include/Wit.h
	cp $(IDIR)/WitResp.h /usr/local/include/WitResp.h

clean:
	rm $(ODIR)/*