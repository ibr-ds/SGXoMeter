# Build Graphene related files as follows:
# normally:
# - make               -- create non-SGX no-debug-log manifest
# - make SGX=1         -- create SGX no-debug-log manifest
# - make SGX=1 DEBUG=1 -- create SGX debug-log manifest
# ---------------------
# We rebuilt the Makefile to always build the GrapheneSGX files, as SGXoMeter always requires SGX execution.
#
# When using Graphene legacy driver, execute "sudo sysctl vm.mmap_min_addr=0" before the first run of "make".
#
# Use `make clean` to remove Graphene-generated files

############################################ CONSTANTS ############################################

# Relative path to Graphene root
GRAPHENEDIR = /opt/marcel/graphene
SGX_SIGNER_KEY ?= $(GRAPHENEDIR)/Pal/src/host/Linux-SGX/signer/enclave-key.pem
BASELINE_DIR = $(shell pwd)
LIBSODIUM_DIR = $(BASELINE_DIR)/../CommonHeaders/Libsodium
TEST_NAME = GrapheneBench 

UBUNTU_VER = $(shell lsb_release --short --id)$(shell lsb_release --short --release)

ifeq ($(DEBUG),1)
GRAPHENE_LOG_LEVEL = debug
else
GRAPHENE_LOG_LEVEL = error
endif

.PHONY: all
#all: GrapheneBench GrapheneBench.manifest
#ifeq ($(SGX),1)
all: GrapheneBench.manifest.sgx GrapheneBench.sig GrapheneBench.token
#endif

include $(GRAPHENEDIR)/Scripts/Makefile.configs


######################################## GrapheneBench MANIFEST ########################################

GrapheneBench.manifest: GrapheneBench.manifest.template
	graphene-manifest \
		-Dlog_level=$(GRAPHENE_LOG_LEVEL) \
		-Darch_libdir=$(ARCH_LIBDIR) \
		-Dbaseline_dir=$(BASELINE_DIR) \
		-Dlibsodium_dir=$(LIBSODIUM_DIR) \
		$< > $@ 
# $< --> name of first prerequisite; $@ --> file name of the target of the rule 
 
GrapheneBench.manifest.sgx: GrapheneBench.manifest GrapheneBench
	graphene-sgx-sign \
		--key $(SGX_SIGNER_KEY) \
		--manifest $< \
		--output $@

GrapheneBench.sig: GrapheneBench.manifest.sgx

GrapheneBench.token: GrapheneBench.sig
	graphene-sgx-get-token \
		--output GrapheneBench.token --sig GrapheneBench.sig



########################### COPIES OF EXECUTABLES #############################

#GrapheneBench: 



############################## RUNNING TESTS ##################################

# .PHONY: normal_GrapheneBench
# normal_GrapheneBench: all 
# 	./GrapheneBench 
# # Anpassen auf richtigen Pfad

# ifeq ($(SGX),)
# GRAPHENE = graphene-direct
# else
# GRAPHENE = graphene-sgx
# endif

# .PHONY: graphene-GrapheneBench
# graphene-GrapheneBench: all
# 	$(GRAPHENE) $(TEST_NAME) 


################################## CLEANUP ####################################
.PHONY: clean
clean:
	$(RM) *.token *.sig *.manifest.sgx *.manifest libdsodium .lck

.PHONY: distclean
distclean: clean
	$(RM) -r $(SRCDIR) GrapheneBench.tar.gz