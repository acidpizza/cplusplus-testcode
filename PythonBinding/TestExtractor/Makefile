# Name of the file(s) we're compiling

TARGET = TestExtractor

# location of the Python header files

PYTHON = /usr/include/python2.7

# location of the Boost Python include files and library

BOOST_INC = /usr/local/include
BOOST_LIB = /usr/local/lib

$(TARGET).so: $(TARGET).o
	g++ -shared -Wl,--export-dynamic \
	$(TARGET).o -L$(BOOST_LIB) -lboost_python \
	-L/usr/lib/python2.1/config -lpython2.7 \
	-o TestExtractor.so

$(TARGET).o: $(TARGET).C
	g++ -I$(PYTHON) -I$(BOOST_INC) -c $(TARGET).C

clean:
	rm -f *.o *.dll *.a *~ core

