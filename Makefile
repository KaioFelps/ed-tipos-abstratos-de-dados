# Variável	Significado													Exemplo com foo.o: foo.c bar.h
# $@		Nome da meta (target)										foo.o
# $<		Primeiro pré-requisito (source)								foo.c
# $^		Todos os pré-requisitos										foo.c bar.h
# $?		Somente os pré-requisitos mais novos que a meta	depende		depende

INCLUDE_DIRS := include vcpkg_installed/x64-linux/include
INCLUDE_FLAGS := $(foreach dir,$(INCLUDE_DIRS),-I $(dir))

LIBS_DIRS := vcpkg_installed/x64-linux/lib vcpkg_installed/x64-linux/lib/manual-link
LIBS_DIRS_FLAGS := $(foreach dir,$(LIBS_DIRS),-L $(dir))

LIBS := 
DEV_LIBS := Catch2Main Catch2

LIBS_FLAGS := $(foreach lib,$(LIBS),-l $(lib))
DEV_LIBS_FLAGS := $(foreach lib,$(DEV_LIBS),-l $(lib))

BUILD_DIR := __build
TESTS_DIR := tests
TESTS_BUILD_DIR := $(BUILD_DIR)/__tests
SRC_DIR := src

TEST_SRCS := $(shell find $(TESTS_DIR) -type f -name "*.cpp")
TEST_BINS := $(patsubst $(TESTS_DIR)/%.cpp,$(TESTS_BUILD_DIR)/%,$(TEST_SRCS))
EXECUTABLE_TESTS_BINS := $(wildcard $(TESTS_BUILD_DIR)/*_test)

SRC_FILES := $(shell find $(SRC_DIR) -type f -name "*.cpp")
SRC_BINS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

COMPILER := clang++
COMPILER_FLAGS := -std=c++20 $(INCLUDE_FLAGS) $(LIBS_DIRS_FLAGS) -Wall -Wextra

SRC_BINS_FOR_TESTS := $(filter-out $(BUILD_DIR)/main.o, $(SRC_BINS))

.PHONY: test clean build

clean:
	rm -rf $(BUILD_DIR)

test: build $(TEST_BINS) | $(TESTS_BUILD_DIR)
	@echo "Rodando os testes do diretório /testes"
	@for test in $(EXECUTABLE_TESTS_BINS); do\
		echo "Rodando o teste $$test";\
		./$$test || exit 1;\
	done
	@echo "Todos os testes passaram."

$(BUILD_DIR):
	@mkdir -p $@

$(TESTS_BUILD_DIR):
	@mkdir -p $@

$(TESTS_BUILD_DIR)/%: $(TESTS_DIR)/%.cpp | build $(TESTS_BUILD_DIR)
	@mkdir -p $(dir $@)
	@$(COMPILER) $(COMPILER_FLAGS) $(SRC_BINS_FOR_TESTS) $< $(LIBS_FLAGS) $(DEV_LIBS_FLAGS) -o $@

# --- build ---

build: $(SRC_BINS)
	@echo "Compilado com sucesso."

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@echo $@

	@if [ "$@" != "$(TESTS_BUILD_DIR)/*" ]; then \
		echo "Compilando $<"; \
		mkdir -p $(dir $@);\
		$(COMPILER) $(COMPILER_FLAGS) -c $< $(LIBS_FLAGS) -o $@; \
	else \
		echo "Ignorando $@"; \
	fi