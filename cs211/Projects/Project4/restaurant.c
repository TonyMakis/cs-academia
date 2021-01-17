#include "queue.h"

/* Corresponding command => a <size> <name>
 * Add the group to the wait list using the given group size and name specifying
 * the group is waiting in the restaurant. The group’s information is added to the 
 * end of the list. If the name already exists in the wait list, give an error 
 * message and do not add the information.
 * 
 * I do not free the malloc'd name field, b/c it is still needed in the queue
 * unless of course the name entered is already in the queue
 */
void doAdd(queue *q) {
    /* get group size from input */
    int size = getPosInt();
    if(size < 1) {
        printf("Error: Add command requires an integer value of at least 1\n");
        printf("Add command is of form: a <size> <name>\n");
        printf("  where: <size> is the size of the group making the reservation\n");
        printf("         <name> is the name of the group making the reservation\n");
        return;
    }

    /* get group name from input */
    char *name = getName();
    if(name == NULL) {
        printf("Error: Add command requires a name to be given\n");
        printf("Add command is of form: a <size> <name>\n");
        printf("  where: <size> is the size of the group making the reservation\n");
        printf("         <name> is the name of the group making the reservation\n");
        return;
    }

    if(doesNameExist(q, name)) { // Then we shouldn't add a duplicate name to queue
        printf("Error: Cannot add group \"%s\"; already exists in queue!\n", name);
        free(name);
    } else { // Can safely add non-duplicate name
        printf("Adding group \"%s\" of size %d\n", name, size);
        addToList(q, size, name, YES);
    }
}

/* Corresponding command => c <size> <name>
 * Add the group to the wait list using the given group size and name specifying 
 * the group as a call ahead group. The group’s information is added to the end 
 * of the list. If the name already exists in the wait list, give an error message 
 * and do not add the information
 * 
 * I do not free the malloc'd name field, b/c it is still needed in the queue
 * unless of course the name entered is already in the queue
 */
void doCallAhead(queue *q) {
    /* get group size from input */
    int size = getPosInt();
    if(size < 1) {
        printf("Error: Call-ahead command requires an integer value of at least 1\n");
        printf("Call-ahead command is of form: c <size> <name>\n");
        printf("  where: <size> is the size of the group making the reservation\n");
        printf("         <name> is the name of the group making the reservation\n");
        return;
    }

    /* get group name from input */
    char *name = getName();
    if(name == NULL) {
        printf("Error: Call-ahead command requires a name to be given\n");
        printf("Call-ahead command is of form: c <size> <name>\n");
        printf("  where: <size> is the size of the group making the reservation\n");
        printf("         <name> is the name of the group making the reservation\n");
        return;
    }

    if(doesNameExist(q, name)) { // Then we shouldn't add a duplicate name to queue
        printf("Error: Cannot add call-ahead group \"%s\"; already exists in queue!\n", name);
        free(name);
    } else { // Can safely add non-duplicate name
        printf("Adding call-ahead group \"%s\" of size %d\n", name, size);
        addToList(q, size, name, NO);
    }
}

/* Corresponding command => w <name>
 * Mark the call ahead group using the given name as waiting in the restaurant.
 * If the name does not exist is the wait list or is not a call ahead group, 
 * give an error message.
 * 
 * I do not need the malloc'd name field after this function returns, so free it
 */
void doWaiting(queue *q) {
    /* get group name from input */
    char *name = getName();
    if(name == NULL) {
        printf("Error: Waiting command requires a name to be given\n");
        printf("Waiting command is of form: w <name>\n");
        printf("  where: <name> is the name of the group that is now waiting\n");
        return;
    }

    if(doesNameExist(q, name)) { // Group exists in queue
        if(updateStatus(q, name)) // Group just arrived
            printf("Waiting group \"%s\" is now in the restaurant\n", name);
        else // Group was already waiting my g
            printf("Waiting group \"%s\" already in the restaurant\n", name);
        
    } else { // Group not found in queue
        printf("Error: Cannot edit group \"%s\"'s status; not in queue!\n", name);
    }

    free(name);
}

/* Corresponding command => r <table-size>
 * Retrieve and remove the first group on the wait list that is waiting in the 
 * restaurant and is less than or equal to the table size. Note that “first” is 
 * the group that has been in the wait list the longest.
 * 
 * if we retrieve the name of a group, free it after we are done printing
 */
void doRetrieve(queue *q) {
    /* get table size from input */
    int size = getPosInt();
    if(size < 1) {
        printf("Error: Retrieve command requires an integer value of at least 1\n");
        printf("Retrieve command is of form: r <size>\n");
        printf("  where: <size> is the size of the group making the reservation\n");
        return;
    }
    clearToEoln();
    printf("Retrieving (and removing) the first group that can fit at a table of size %d\n", size);

    char *nameRetrieved = retrieveAndRemove(q, size);
    if(nameRetrieved != NULL) {
        printf("Group %s retrieved\n", nameRetrieved);
        free(nameRetrieved);
    } else {
        printf("Group of size %d could not be retrieved\n", size);
    }
}

/* Corresponding command => l <name>
 * List total number of groups that are in the wait list in front of the group 
 * specified by the given name. Also list the size of each group that are in the 
 * wait list ahead of the group specified by the given name. 
 * If the name does not exist, give an error message.
 * 
 * I do not need the malloc'd name field after this function returns, so free it
 */
void doList(queue *q) {
    /* get group name from input */
    char *name = getName();
    if(name == NULL) {
        printf ("Error: List command requires a name to be given\n");
        printf ("List command is of form: l <name>\n");
        printf ("  where: <name> is the name of the group to inquire about\n");
        return;
    }
    
    if(doesNameExist(q, name)) { // Group exists in queue
        printf("Group \"%s\" is behind the following %d group(s)\n",
               name, countGroupsAhead(q, name));
        displayGroupSizeAhead(q, name);
        printf("\n");
    } else { // Group not found in queue
        printf("Error: Cannot list this group \"%s\"; not in queue!\n", name);
    }

    free(name);
}

/* Corresponding command => d
 * Display the total number of groups in the wait list. Also display the names,
 * group size and in-restaurant status of all groups in the wait list in order 
 * from first to last.
 */
void doDisplay(queue *q) {
    clearToEoln();
    printf ("Display information about all groups\n");   
    displayListInformation(q);
}
