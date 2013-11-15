PRJ_DIR =.
PRJ_OBJS_FILE=prjObjs.lst
PRJ_OBJS =bktest.o oemfb.o oemfbtab.o
PRJ_TYPE =vxApp
PRJ_LIBS = test.a
DEFAULT_RULE=bkcfc.out
PRJ_OBJS_FOR_NM=@$(PRJ_OBJS_FILE)
PRJ_OBJS_FOR_LD_PARTIAL=-Wl,$(PRJ_OBJS_FOR_NM)
include make.default

$(PRJ_OBJS_FILE): makefile
	-$(RM) $@
	@echo Generating $(subst \,/, $@)...
	@$(MAKE) --no-print-directory -f makefile $@_make > $(PRJ_OBJS_FILE)

$(PRJ_OBJS_FILE)_make : $(foreach obj,$(PRJ_OBJS),$(obj)_._write_._)

# We have one "write" target per project object. Each one
# writes the name of the object to stdout.
# The point of using "_._write_._" is simply to ensure
# that the targets have odd enough names that they don't
# clash with any existing targets.

$(foreach obj,$(PRJ_OBJS),$(obj)_._write_._) :
	@echo $(subst _._write_._,,$@)


bktest.o:bktest.cpp
	$(CC) $(CFLAGS) -c $<
	
oemfb.o:oemfb.c
	$(CC) $(CFLAGS) -c $<
	
oemfbtab.o:oemfbtab.c
	$(CC) $(CFLAGS) -c $<