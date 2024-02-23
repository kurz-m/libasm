################################################################################
###############                GENERAL SETTINGS                   ##############
################################################################################

NAME := libasm.a
.DEFAULT_GOAL := all
CC := cc
AR := ar
AS := nasm
RM := rm -rf
OS := $(shell uname -s)

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
LIB_DIR := lib
BIN_DIR := bin
INC_DIRS := .
SRC_DIRS := .

# Tell the Makefile where headers and source files are
vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

################################################################################
###############                      FILES                        ##############
################################################################################

SRCS := ft_strlen.asm
OBJS := $(addprefix $(BUILD_DIR)/, $(SRCS:%.asm=%.o))
INC := compiler_macros.inc os_syscalls.inc
TEST_HEADER :=

LIBASM := $(addprefix $(LIB_DIR), $(NAME))

################################################################################
########                           FLAGS                        ################
################################################################################

CFLAGS ?= -Wextra -Wall -Werror -g -MMD -MP $(addprefix -I, $(INC_DIRS))
ARFLAGS ?= -rcs
ASFLAGS ?= -Wall $(addprefix -iinc, $(INC_DIRS))
LDFLAGS ?= 

ifeq ($(DEBUG),)
	CFLAGS += -g
	ASFLAGS += -g
else
	CFLAGS += -O2
endif

################################################################################
########                        OS specific                     ################
################################################################################

ifeq ($(OS), Linux)
	ASFLAGS += -f elf64 -d__linux__
else ifeq ($(OS), Darwin)
	ASFLAGS += -f macho64 -d__APPLE__
else
	$(error Unsupported operating system: $(OS). Works only under Linux/MacOS)
endif

CC_TYPE := $(shell cc --version 2>/dev/null | grep -o -E '(Ubuntu|Debian)')

ifeq ($(CC_TYPE),)
	CC_TYPE := $(shell cc --version 2>/dev/null | grep -o -E '(gcc|clang)')
	ifeq ($(CC_TYPE), gcc)
		ASFLAGS += -d__GNUC__
	else ifeq ($(CC_TYPE), clang)
		ASFLAGS += -d__clang__
	else
		$(error Unsupported compiler: $(CC_TYPE).)
	endif
else
	ASFLAGS += -d__GNUC__
endif


################################################################################
########                         COMPILING                      ################
################################################################################

all: $(LIB_DIR)/$(NAME)

$(LIB_DIR)/$(NAME): $(OBJS) | $(LIB_DIR)
	@$(LOG) "Linking object files to $@"
	@$(AR) $(ARFLAGS) $@ $^

$(LIB_DIR):
	@mkdir -p $@

$(BUILD_DIR)/%.o: %.asm $(INC) | $(BUILD_DIR)
	@$(LOG) "Compiling $(notdir $@)"
	@$(AS) $(ASFLAGS) $< -o $@

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
	@if [ -d "$(LIB_DIR)" ]; then \
		$(LOG) "Cleaning $(notdir $(NAME))"; \
		$(RM) $(LIB_DIR); \
	else \
		$(LOG) "No library to clean."; \
	fi

re: fclean all

-include $(OBJS:%.o=%.d)

.PHONY: all fclean clean re
