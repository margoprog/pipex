TOUS LES TESTS DANS `bash --posix`


av[0]	av[1]		av[2]	av[3]		av[4]	av[5]
./pipex	"infile"	"cat -e"	"grep a"	"wc -l" "outfile"
ac = 6;
nb = ac - 3;
< infile cat  grep a | wc -l > outfile

int fd[2];
pipe(fd);
fd[0] = LECTURE
fd[1] = ECRITURE

cat LIT dans infile
cat ECRIT dans le pipe cat | grep
grep LIT dans le pipe cat | grep
grep ECRIT dans le pipe grep | wc
wc LIT dans le pipe grep | wc
wc ECRIT dans le outfile


La fonction retourne 0 si l'action spécifiée peut être effectuée
sur le fichier ou répertoire ou -1 si l'action ne peut pas être effectuée
ou si une erreur s'est produite.




/*

1ere ETAPE
	lire dans la variable **env,
	recuperer la variable "PATH=" a l'interieur
	la stocker dans ta structure apres l'avoir split au ":"

2eme ETAPE
	fonction qui va prendre en argument une commande et le PATH
	et verifier si la commande existe dans le PATH a l'aide de access();

3eme ETAPE

*/

 < infile ls -l | wc -l > outfile
 < Makefile ls -l | wc -l > test.txt

# PIPEX :
## Objectif :
- ###  imiter la commande "|" en shell
## comment coder PIPEX :
```c
//ouvrir des forks pour chacune des fonctions a realisees

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		tube[2];
	int		infile;
	int		outfile;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
}t_pipex;

int main()
{
	//dans une struct t_pipex stocker

	//les deux fd des fichiers que l'on open
	//le path jusqua la commande a appelle
	//le premier child
	//pipe(pipex.tube)
		//on appelle first_child(t_pipex)
	//le second child
	//pipe(pipex.tube)
		//on appelle second_child(t_pipex)
	//utilise une fonction close_pipe() afin de gerer les entree et les sorties des pipes
	//attendre les pid des child
	//free()
	//fin de programme

}
void first_child()
{
	//dup2 la sortie du tube avec la sortie standard
	//close l'entree du tube ouverte par pipe
	//dup2 le ficher infile et l'entree standard
	//recuperer les arguments de la commande
	//recuperer la commande avec le path et les arguments
	//executer la commande
}
void second_child()
{
	//dup2 l'entree du tube avec l'entree standard
	//close la sortie du tube
	//dup2 le ficher outfile et la sortie standar
	//recuperer les arguments de la commande
	//recuperer la commande avec le path et les arguments
	//executer la commande
}
```
## fonctions autorises non connu:
- # perror
	## prototype :
	```C
	#include <stdio.h>
	void perror( const char * prefix );
	```
	## envoie sur la sortie erreur, un message d'erreur associe a errno (obtenu grace a <errno.h>)
	---
	## Parametres :
	```
	precede le message d'erreur par un message personnalise
	```
- # strerror
	## prototype :
	```C
	#include <string.h>
	char * strerror ( int errCode );
	```
	## affiche sur la sortie erreur un message associe a un code erreur que l'on recupere via errno
	## Il n'est pas necessaire de free la chaine recuperee
	---
	## Parametres :
	le code erreur pour lequel retrouver le message d'erreur
- # access
	## prototype :
	```C
	#include <unistd.h>
	int access(const char *pathname, int mode);
	```
	## Permet de verifier l'existence et les permission d'acces a un fichier renvoie 0 si autorise sinon -1 et la variable errno sera fixee avec le code erreur
	---
	## Parametres :
	- pathname :
	chemin jusqu'au fichier
	- mode:
	mode d'acces a tester
	F_OK : existence
	R_OK : lecture du fichier
	W_OK : ecriture du fichier
	X_OK : execution du fichier
	## ERREURS :
	- EACCES : l'accès au fichier est refusé en raison de restrictions d'accès.
	- EFAULT : le pointeur pathname spécifié en paramètre pointe en dehors de l'espace d'adressage autorisé.
	- EINTR : la valeur du paramètre aMode est invalide.
	- ELOOP : le chemin spécifié contient une référence circulaire, certainement au travers d'un lien symbolique.
	- ENAMETOOLONG : le chemin spécifié dépasse PATH_MAX caractères, ou l'un de ses éléments constitutifs dépasse NAME_MAX.
	- ENOENT : le chemin spécifié n'existe pas.
	- ENOMEM : il n'y a plus assez de mémoire pour le noyau.
	- ENOTDIR : un des éléments du chemin spécifié n'est pas un dossier.
	- EROFS : un accès en écriture est demandé sur un système de fichier read-only.
- # dup && dup2
	## prototype
	```c
	#include <unistd.h>
	int dup(int oldfd);
	int dup2(int oldfd, int newfd)
	```
	# creer une copie du descripteur de fichier
	dup utilise le plus petit numero inutilise pour le nouveau decripteur
	dup transforme newfd en une copie de oldfd, en fermant auparavant newfd sauf si oldfd n'est pas un descripteur de fichier ou si oldfd et newfd on la meme valeur
	---
	## parametres :
	- oldfd anciens file descriptor
	- newfd nouveau file descriptor
	## renvoie le nouveau descripteur ou -1 si ils echouent errno contiendra le code erreur
	## ERREURS :
	- EBADF
	oldfd n'est pas un descripteur de fichier ouvert, ou newfd n'est pas dans les valeurs autorisées pour un descripteur.
	- EBUSY
	(Linux seulement) Cette valeur peut être retournée par dup2() lors d'une concurrence critique avec open(2) et dup().
	- EINTR
	L'appel dup2() a été interrompu par un signal ; voir signal(7).
	- EMFILE
	Le processus dispose déjà du nombre maximum de descripteurs de fichier autorisés simultanément, et tente d'en ouvrir un nouveau.
- # execve
	## prototype
	```c
	#include <unistd.h>
	int execve(const char *fichier, char *const argv[],char *const envp[]);
	```
	## executer un programme
	---
	## parametre :
	- argc nombre d'arguments
	- argv tableau de chaine d'arguments
	- envp tableau de chaine sous forme cle=valeur
	## ERREURS :
	- E2BIG
	Le nombre total d'octets dans l'environnement (envp) et dans la liste d'arguments (argv) est trop grand.
	- EACCES
	La permission de parcours est refusée pour un des composants du chemin filename ou du nom d'un interpréteur de script. (Voir aussi path_resolution(7).)
	- EACCES
	Le fichier ou l'interpréteur de scripts n'est pas un fichier régulier.
	- EACCES
	L'autorisation d'exécution est refusée pour le fichier, ou un script, ou un interpréteur ELF.
	- EACCES
	Le système de fichiers est monté avec l'option noexec.
	- EFAULT
	L'argument fichier pointe en dehors de l'espace d'adressage accessible.
	- EINVAL
	Un exécutable ELF a plusieurs segments PT_INTERP (indique plusieurs interpréteurs).
	- EIO
	Une erreur d'entrée-sortie s'est produite.
	- EISDIR
	L'interpréteur ELF cité est un répertoire.
	- ELIBBAD
	L'interpréteur ELF mentionné n'est pas dans un format connu.
	- ELOOP
	Le chemin d'accès au fichier, ou au script, ou à l'interpréteur ELF contient une référence circulaire (à travers un lien symbolique).
	- EMFILE
	Le nombre maximal de fichiers ouverts par processus est atteint.
	ENAMETOOLONG
	La chaîne de caractères fichier est trop longue.
	- ENFILE
	La limite du nombre total de fichiers ouverts sur le système a été atteinte.
	- ENOENT
	Le fichier ou un script ou un interpréteur ELF n'existe pas, ou une bibliothèque partagée nécessaire pour le fichier ou l'interpréteur n'est pas disponible.
	- ENOEXEC
	Le fichier exécutable n'est pas dans le bon format, ou est destiné à une autre architecture.
	- ENOMEM
	Pas assez de mémoire pour le noyau.
	- ENOTDIR
	Un élément du chemin d'accès à fichier à un script ou à l'interpréteur ELF n'est pas un répertoire.
	- EPERM
	Le système de fichiers est monté avec l'attribut nosuid et le fichier a un bit Set-UID ou Set-GID positionné.
	- EPERM
	Le processus est suivi avec ptrace(2), l'utilisateur n'est pas le superutilisateur, et le fichier a un bit Set-UID ou Set-GID positionné.
	- ETXTBSY
	Le fichier exécutable a été ouvert en écriture par un ou plusieurs processus.
- # fork
	## prototype
	```c
	#include <unistd.h>
	pid_t fork(void);
	```
	## creer un nouveau processus en depliquant le processus appelant. Le nouveau processus que l'on appelle "fil" est la copie exacte appelant on l'appelle processus "pere" ou "parent"
	## Le PID du fils est envoyee au processus parent et 0 est envoye au processus fils. En cas d'echec -1 est renvoye et errno et defini au code d'echec
	EAGAIN : fork() ne peut pas allouer assez de mémoire pour copier la table des pages du père et une structure de tâche pour le fils.
	EAGAIN : Il n'a pas été possible de créer un nouveau processus car la limite ressource RLIMIT_NPROC de l'appelant a été rencontrée. Pour franchir cette limite, le processus doit avoir au moins l'une des deux capacités CAP_SYS_ADMIN ou CAP_SYS_RESOURCE.
	ENOMEM : fork() a échoué car le noyau n'a plus assez de mémoire.
- # pipe
	## prototype
	```c
	unistd.h
	int pipe(int pipefd[2]);
	```
	## Parametres
	- pipefd[0] est un fd faisant reference a lextremite de lecture
	- pipefd[1] fait reference a lextremite d'ecriture

- # unlink
	## prototype
	```c
	#include <unistd.h>
	int unlink(const char *pathname);
	```
	## detruit un nom et eventuelement un fichier associe renvoie 0 si il reussit -1 si il echoue
	## Parametre :
	- chemin du fichier a detruire
	## ERREURS :
	- EACCES
	L'accès en écriture au répertoire contenant pathname n'est pas autorisé pour l'UID effectif du processus, ou bien l'un des répertoires de pathname n'autorise pas le parcours. (Voir aussi path_resolution(7).)
	- EBUSY (spécifique Linux)
	Le fichier pathname ne peut pas être détruit avec unlink car il est utilisé par le système ou par un autre processus, et l'implémentation considère que c'est une erreur.
	- EFAULT
	pathname pointe en dehors de l'espace d'adressage accessible
	EIO
	Une erreur d'entrée-sortie s'est produite.
	- EISDIR
	pathname est un répertoire. (Il s'agit d'une erreur non-POSIX renvoyée par Linux depuis la version 2.1.132).
	- ELOOP
	Trop de liens symboliques dans le chemin d'accès pathname.
	ENAMETOOLONG
	pathname est trop long.
	- ENOENT
	Un répertoire dans le chemin d'accès pathname n'existe pas ou est un lien symbolique pointant nulle part, ou pathname est vide.
	- ENOMEM
	Pas assez de mémoire pour le noyau.
	- ENOTDIR
	Un élément du chemin d'accès pathname n'est pas un répertoire.
	- EPERM
	Le système ne permet pas la destruction des répertoires avec unlink, ou cette destruction nécessite des privilèges que le processus appelant n'a pas. (Il s'agit d'une erreur conseillée par POSIX, comme indiqué plus haut. Dans ce cas, Linux renvoie EISDIR).
	- EPERM (spécifique Linux)
	Le système de fichiers ne permet pas la destruction avec unlink.
	- EPERM ou EACCES
	Le répertoire contenant pathname a son sticky bit (S_ISVTX) à 1, et l'UID effectif du processus n'est ni celui du fichier ni celui du répertoire et le processus n'est pas privilégié (sous Linux : n'a pas la capacité CAP_FOWNER).
	- EROFS
	pathname est placé sur un système de fichiers en lecture seule
- # wait && waitpid
	## prototype :
	```c
	#include <sys/types.h>
	#include <sys/wait.h>
	pid_t wait(int *status);
	pid_t waitpid(pid_t pid, int *status, int options);
	```
	## appels systeme utilises pour attendre le changement d'etat du fils d'un processus appelant.
	L'appel système wait() suspend l'exécution du processus appelant jusqu'à ce que l'un de ses fils se termine. L'appel wait(&status) est équivalent à :
	```c
	    waitpid(-1, &status, 0);
	```
	L'appel système waitpid() suspend l'exécution du processus appelant jusqu'à ce que le fils spécifié par son pid ait changé d'état. Par défaut, waitpid() n'attend que les fils terminés, mais ce comportement est modifiable avec l'argument options comme décrit plus loin.
	La valeur de pid peut être l'une des suivantes :
	< -1
	attendre la fin de n'importe lequel des processus fils dont le GID du processus est égal à la valeur absolue de pid.
	-1
	attendre n'importe lequel des processus fils.
	0
	attendre n'importe lequel des processus fils dont le GID du processus est égal à celui du processus appelant.
	">0"
	attendre n'importe lequel des processus fils dont le PID est égal à pid.
	## ERREURS :msg_error(ERR_INFILE);aussi path_resolution(7).)
	- EBUSY (spécifique Linux)
	Le fichier pathname ne peut pas être détruit avec unlink car il est utilisé par le système ou par un autre processus, et l'implémentation considère que c'est une erreur.
	- EFAULT
	pathname pointe en dehors de l'espace d'adressage accessible
	EIO
	Une erreur d'entrée-sortie s'est produite.
	- EISDIR
	pathname est un répertoire. (Il s'agit d'une erreur non-POSIX renvoyée par Linux depuis la version 2.1.132).
	ELOOP
	Trop de liens symboliques dans le chemin d'accès pathname.
	- ENAMETOOLONG
	pathname est trop long.
	- ENOENT
	Un répertoire dans le chemin d'accès pathname n'existe pas ou est un lien symbolique pointant nulle part, ou pathname est vide.
	- ENOMEM
	Pas assez de mémoire pour le noyau.
	- ENOTDIR
	Un élément du chemin d'accès pathname n'est pas un répertoire.
	- EPERM
	Le système ne permet pas la destruction des répertoires avec unlink, ou cette destruction nécessite des privilèges que le processus appelant n'a pas. (Il s'agit d'une erreur conseillée par POSIX, comme indiqué plus haut. Dans ce cas, Linux renvoie EISDIR).
	EPERM (spécifique Linux)
	Le système de fichiers ne permet pas la destruction avec unlink.
	- EPERM ou EACCES
	Le répertoire contenant pathname a son sticky bit (S_ISVTX) à 1, et l'UID effectif du processus n'est ni celui du fichier ni celui du répertoire et le processus n'est pas privilégié (sous Linux : n'a pas la capacité CAP_FOWNER).
	- EROFS
	pathname est placé sur un système de fichiers en lecture seule
