NAME = avm

HEADERS = 	
			
INCDIR = ./includes
SRCDIR = ./sources
HFILES = $(patsubst %, $(INCDIR)/%.hpp, $(HEADERS))

FILENAMES =	main 

CFILES = $(patsubst %, $(SRCDIR)/%.cpp, $(FILENAMES))
OFILES = $(patsubst %, $(ODIR)/%.o, $(FILENAMES))

FLAGS = -Wall -Wextra -Werror 
ODIR = ./obj

BLACK = '\033[0;30m'
RED = '\033[0;31m'
GREEN = '\033[0;32m'
BROWN = '\033[0;33m'
BLUE = '\033[0;34m'
PURPLE = '\033[0;35m'
CYAN = '\033[0;36m'
LGRAY = '\033[0;37m'
DGRAY = '\033[1;30m'
LRED = '\033[1;31m'
LGREEN = '\033[1;32m'
YELLOW = '\033[1;33m'
LBLUE = '\033[1;34m'
PINK = '\033[1;35m'
LCYAN = '\033[1;36m'
WHITE = '\033[1;37m'
NC = '\033[0m' # No Color

all: $(NAME)

$(NAME): $(ODIR) $(HFILES) $(OFILES)
	@echo ${CYAN}[Compiling the $(NAME) executable]${NC}
	clang++ $(FLAGS) -lncurses $(OFILES) $(LIBFT) -o $(NAME) 
	@echo ${GREEN}"[========| $(NAME) is up to date. |========]"${NC}

$(ODIR)/%.o: $(SRCDIR)/%.cpp $(HFILES)
	clang++ $(FLAGS) -o $@ -c $< -I$(INCDIR)

$(ODIR):
	@mkdir -p $(ODIR)

clean:
	@echo ${RED}[Removing $(NAME) *.o files]${NC}
	@/bin/rm -rf $(ODIR)
	
fclean: clean
	@echo ${RED}[Removing executable $(NAME) file]${NC}
	@/bin/rm -f $(NAME)

re: fclean all
