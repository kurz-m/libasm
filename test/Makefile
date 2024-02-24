################################################################################
###############                GENERAL SETTINGS                   ##############
################################################################################

NAME := libasm_test
.DEFAULT_GOAL := all
CXX := c++
RM := rm -rf

################################################################################
###############                 PRINT OPTIONS                     ##############
################################################################################

G := \033[32m
X := \033[0m
BO := $(shell tput bold)
LOG := printf "[$(BO)$(G)ⓘ INFO$(X)] %s\n"

################################################################################
###############                  DIRECTORIES                      ##############
################################################################################

BUILD_DIR := build
LIB_DIR := ../lib
BIN_DIR := bin
INC_DIRS := . ..
SRC_DIRS := .

# Tell the Makefile where headers and source files are
vpath %.h $(INC_DIRS)
vpath %.hpp $(TEST_DIR)

################################################################################
###############                      FILES                        ##############
################################################################################

SRCS := $(wildcard *.cpp)
OBJS := $(addprefix $(BUILD_DIR)/, $(SRCS:%.cpp=%.o))

################################################################################
########                           FLAGS                        ################
################################################################################

CXXFLAGS ?= -c -Wextra -Wall -Werror -MMD -MP $(addprefix -I, $(INC_DIRS))
LDFLAGS ?= $(addprefix -L, $(LIB_DIR))
LDLIBS ?= -lasm

ifeq ($(DEBUG),)
	CFLAGS += -g
else
	CFLAGS += -O2
endif

################################################################################
########                         COMPILING                      ################
################################################################################

all: $(NAME)

$(NAME): $(LIB_DIR)/libasm.a $(OBJS)
	@$(LOG) "Linking object files to $@"
	@$(CXX) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(LIB_DIR)/libasm.a:
	$(MAKE) -C .. all

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@$(LOG) "Compiling $(notdir $@)"
	@$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@if [ -d "$(BUILD_DIR)" ]; then \
		$(LOG) "Cleaning $(notdir $(BUILD_DIR))"; \
		$(RM) $(BUILD_DIR); \
	else \
		$(LOG) "No objects to clean."; \
	fi

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		$(LOG) "Cleaning $(notdir $(NAME))"; \
		$(RM) $(NAME); \
	else \
		$(LOG) "No executable to clean."; \
	fi

re: fclean all

-include $(OBJS:%.o=%.d)

.PHONY: all fclean clean re
