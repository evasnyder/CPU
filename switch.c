#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/* Flag set by ‘--verbose’. */
static int verbose_flag;

int
main (int argc, char **argv)
{
  int c;

  while (1)
    {
      static struct option long_options[] =
        {
          /* These options set a flag. */
          {"verbose", no_argument,       &verbose_flag, 1},
          {"brief",   no_argument,       &verbose_flag, 0},
          /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"procgen-file",     no_argument,       0, 'f'},
          {"num-cpus",  no_argument,       0, 'c'},
          {"quantum",  required_argument, 0, 'q'},
          {"stop-time",  required_argument, 0, 't'},
          {"switch-time",    required_argument, 1, 'w'},
          {"no-io-faults",  required_argument, 0, 'n'},
          {"verbose",  required_argument, 0, 'v'},
          {"batch",    required_argument, 0, 'b'},
          {"help",    required_argument, 0, 'w'},
          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

      c = getopt_long (argc, argv, "abc:d:f:",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;

      switch (c)
        {
        case 0:
          /* If this option set a flag, do nothing else now. */
          if (long_options[option_index].flag != 0)
            break;
          printf ("option %s", long_options[option_index].name);
          if (optarg)
            printf (" with arg %s", optarg);
          printf ("\n");
          break;

        case 'f':
          puts ("option -f\n");
          break;

        case 'c':
          puts ("option -c\n");
          break;

        case 'q':
          printf ("option -q with value `%s'\n", optarg);
          break;

        case 't':
          printf ("option -t with value `%s'\n", optarg);
          break;

        case 'w':
          printf ("option -w with value `%s'\n", optarg);
          break;

        case 'n':
          printf ("option -n with value `%s'\n", optarg);
          break;

        case 'v':
          printf ("option -v with value `%s'\n", optarg);
          break;

        case 'b':
          printf ("option -b with value `%s'\n", optarg);
          break;

        case 'h':
          printf ("option -h with value `%s'\n", optarg);
          break;

        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          abort ();
        }
    }

  /* Instead of reporting ‘--verbose’
     and ‘--brief’ as they are encountered,
     we report the final status resulting from them. */
  if (verbose_flag)
    puts ("verbose flag is set");

  /* Print any remaining command line arguments (not options). */
  if (optind < argc)
    {
      printf ("non-option ARGV-elements: ");
      while (optind < argc)
        printf ("%s ", argv[optind++]);
      putchar ('\n');
    }

  exit (0);
}