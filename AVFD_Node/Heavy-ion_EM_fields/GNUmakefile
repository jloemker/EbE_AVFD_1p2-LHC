all	: EM_fields.e

EM_fields.e	:
		(mkdir build; cd build; cmake ..; make; make install)

distclean	:
	rm *.e
	rm -rf build
	(cd src; make distclean)
