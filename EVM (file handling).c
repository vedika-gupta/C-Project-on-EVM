#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CANDIDATE_COUNT

#define CANDIDATE1 "VEDIKA GUPTA"
#define CANDIDATE2 "ARJUN MARRI"
#define CANDIDATE3 "ADITHI POLAMONI"
#define CANDIDATE4 "BHAGYA MAM"

int votesCount1 = 0, votesCount2 = 0, votesCount3 = 0, votesCount4 = 0, spoiledtvotes = 0;
static char *VOTERS_FILE_PATH = "E:/D Drive/C project on EVM/Voters.csv";
static char *VOTES_FILE_PATH = "E:/D Drive/C project on EVM/Votes.csv";

int isVoterIdExistingInFile(char *filePath, char *voterId)
{

    int isVoterExisting = 0;

    FILE *fp = fopen(filePath, "r");
    if (!fp)
    {
        printf("Can't open file\n");
        return isVoterExisting;
    }
    char buf[1024];
    int field_count = 0;
    char *field;
    while (fgets(buf, 1024, fp))
    {
        if (strstr(buf, voterId) != NULL)
        {
            isVoterExisting = 1;
        }

        field_count = 0;
        field = strtok(buf, ",");

        if (isVoterExisting == 1)
        {

            while (field)
            {
                if (field_count == 0)
                {
                    printf("\nVoter ID:\t");
                }
                if (field_count == 1)
                {
                    if (filePath == VOTERS_FILE_PATH)
                    {
                        printf("NAME:\t");
                    }
                    else
                    {
                        printf("Candidate ID:\t");
                    }
                }
                if (field_count == 2)
                {
                    if (filePath == VOTERS_FILE_PATH)
                    {
                        printf("AGE:\t");
                    }
                    else
                    {
                        printf("Candidate Name:\t");
                    }
                }
                printf("%s\n", field);
                field = strtok(NULL, ",");

                field_count++;
            }

            break;
        }
    }
    fclose(fp);

    return isVoterExisting;
}

int isVoterExists(char *voterId)
{
    int voterExisting = isVoterIdExistingInFile(VOTERS_FILE_PATH, voterId);
    return voterExisting;
}

int isVotedAlready(char *voterId)
{
    int voted = isVoterIdExistingInFile(VOTES_FILE_PATH, voterId);
    return voted;
}

void saveVote(char *voterId, int candidateId, char *candidateName)
{
    FILE *fp = fopen(VOTES_FILE_PATH, "a");
    fprintf(fp, "%s, %d, %s\n", voterId, candidateId, candidateName);
    fclose(fp);
}

void castVote()
{
    char *voterID = malloc(sizeof(char) * 66);
    printf("Enter the Voter ID:");
    scanf("%s", voterID);

    int isVoterExisting = isVoterExists(voterID);
    int isVoted = isVotedAlready(voterID);
    if (isVoterExisting == 1 && isVoted == 0)
    {
        printf("\n");

        int choice;
        printf("\n\n ### Please choose your Candidate ####\n\n");
        printf("\n 1. %s", CANDIDATE1);
        printf("\n 2. %s", CANDIDATE2);
        printf("\n 3. %s", CANDIDATE3);
        printf("\n 4. %s", CANDIDATE4);
        printf("\n 5. %s", "None of These");
        printf("\n\n Input your choice (1 - 5) : ");
        scanf("%d", &choice);

        char *candidateName;
        switch (choice)
        {
        case 1:
            votesCount1++;
            candidateName = CANDIDATE1;
            break;
        case 2:
            votesCount2++;
            candidateName = CANDIDATE2;
            break;
        case 3:
            votesCount3++;
            candidateName = CANDIDATE3;
            break;
        case 4:
            votesCount4++;
            candidateName = CANDIDATE4;
            break;
        case 5:
            spoiledtvotes++;
            break;
        default:
            printf("\n Error: Wrong Choice !! Please retry");
            getchar();
        }
        if (candidateName != NULL)
        {
            saveVote(voterID, choice, candidateName);
        }

        printf("\n thanks for vote !!");
    }
    else
    {
        if (isVoterExisting == 0)
        {
            printf("\n Sorry, there is no voter with this vote id !!");
        }
        else if (isVoted == 1)
        {
            printf("\n Already casted the vote !!");
        }
    }
}

void votesCount()
{
    printf("\n\n ##### Voting Statics ####");
    printf("\n %s - %d ", CANDIDATE1, votesCount1);
    printf("\n %s - %d ", CANDIDATE2, votesCount2);
    printf("\n %s - %d ", CANDIDATE3, votesCount3);
    printf("\n %s - %d ", CANDIDATE4, votesCount4);
    printf("\n %s - %d ", "Spoiled Votes", spoiledtvotes);
}

void getLeadingCandidate()
{
    printf("\n\n  #### Leading Candidate ####\n\n");
    if (votesCount1 > votesCount2 && votesCount1 > votesCount3 && votesCount1 > votesCount4)
        printf("[%s]", CANDIDATE1);
    else if (votesCount2 > votesCount3 && votesCount2 > votesCount4 && votesCount2 > votesCount1)
        printf("[%s]", CANDIDATE2);
    else if (votesCount3 > votesCount4 && votesCount3 > votesCount2 && votesCount3 > votesCount1)
        printf("[%s]", CANDIDATE3);
    else if (votesCount4 > votesCount1 && votesCount4 > votesCount2 && votesCount4 > votesCount3)
        printf("[%s]", CANDIDATE4);
    else
        printf("----- Warning !!! No-win situation----");
}

// Main Function

int main()
{
    int i, choice;
    printf("\n###### -------Welcome to Election/Voting 2021------- #####\n");

    do
    {
        printf("\n\n ###### -------  MENU  ------- #####");
        printf("\n 1. Cast the Vote");
        printf("\n 2. Find Vote Count");
        printf("\n 3. Find leading Candidate");
        printf("\n 0. Exit");

        printf("\n\n Please enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            castVote();
            break;
        case 2:
            votesCount();
            break;
        case 3:
            getLeadingCandidate();
            break;
        default:
            printf("\n VOTING IS DONE!!!! Press a key to exit poll.");
        }
    } while (choice != 0);
    getchar();

    return 0;
}
