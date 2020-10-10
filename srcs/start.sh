#Maintainer ;
# Lturbang, Alyovano

#Il faudra juste ajouter les .c a compiler

RED='\033[0;31m'
UNDERLINE_CYAN='\033[4;36m'
UNDERLINE_GREEN='\033[4;32m'
NC='\033[0m' # No Color
DEBBUG='-fsanitize=address'
FLAGS='-Wall -Werror -Wextra'

#---------------------------------------------------
#Libft Compilation
echo "\n\n"
echo "${UNDERLINE_GREEN}Compilation de la libft${NC}\n\n"
make -C ./libft
mv ./libft/libftprintfgnl.a ./
#---------------------------------------------------
#Compilation Parsing
echo "\n\n"
echo "${UNDERLINE_GREEN}Compilation du parseur${NC}\n\n"
gcc -c ./parsing/*.c
mv ./parsing/*.o ./
#---------------------------------------------------
#Compilation Utilos (Contient aussi quote multilignes)
echo "\n\n"
echo "${UNDERLINE_GREEN}Compilation des utils${NC}\n\n"
gcc -c ./utils/*.c
mv ./utils/*.o ./
#---------------------------------------------------
#Compilation minishell_
echo "\n\n"
echo "${UNDERLINE_GREEN}Compilation du main minishell${NC}\n\n"
gcc -c ./minishell/*.c
mv ./minishell/*.o ./
#---------------------------------------------------
#Compilation basique
echo "\n\n${UNDERLINE_GREEN}Creation de l'executable${NC}\n\n"
#gcc ${FLAGS} *.o libftprintfgnl.a
#Compilation de deboguage
#Mets la basique en com et utilise celle-ci, si t'as une galere
gcc ${FLAGS} ${DEBBUG} *.o libftprintfgnl.a
#---------------------------------------------------
#Clean up
echo "\n\n${UNDERLINE_CYAN} Clean and ready${NC}\n\n"
rm -f *.o libftprintfgnl.a && ./a.out
#echo "\n\n OK \n\n"
#rm a.out
#---------------------------------------------------
