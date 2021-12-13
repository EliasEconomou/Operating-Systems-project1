
PROGRAMS = $(subst programs/, , $(wildcard programs/*))

# Compile all programs
all: programs

programs-%:
	$(MAKE) -C programs/$*

programs: $(addprefix programs-, $(PROGRAMS))

# Clean all programs
clean-programs-%:
	$(MAKE) -C programs/$* clean

clean: $(addprefix clean-programs-, $(PROGRAMS))
	