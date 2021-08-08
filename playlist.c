//Taha Kashaf
//180020889
//AC21008 - Multi-Paradigm Programming and Data Structures.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

/* Create a new, empty playlist, storing a pointer to it in the variable 
   provided (e.g. listPtr) */
int createPlaylist(Playlist **listPtr) {
	
	if(listPtr == NULL)
		return  INVALID_INPUT_PARAMETER;

	if(*listPtr != NULL)
		return INVALID_INPUT_PARAMETER;

	*listPtr = (Playlist*)myMalloc(sizeof(Playlist));

	// check for memory failure
	if(*listPtr == NULL)
	{
		return MEMORY_ALLOCATION_ERROR;
	}

	(*listPtr)->head = NULL;
	(*listPtr)->tail = NULL;
	(*listPtr)->curr = NULL;

	return SUCCESS;
}

/* Add a new MP3 track into the playlist immediately
   BEFORE the current position in the list */
int insertBeforeCurr(Playlist* listPtr, char trackName[], int trackLength) {
	
	if (listPtr == NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	if (trackName == 0) {
		return INVALID_INPUT_PARAMETER;
	}

	if (strlen(trackName) > 49 || strlen(trackName) < 1) {
		return INVALID_INPUT_PARAMETER;
	}

	if (trackLength < 1) {
		return INVALID_INPUT_PARAMETER;
	}

	MP3Track *pNewTrack;
	pNewTrack = (MP3Track*)myMalloc(sizeof(MP3Track));

	if (pNewTrack == NULL) {
		return MEMORY_ALLOCATION_ERROR;
	}

	strcpy(pNewTrack->trackName, trackName)
	pNewTrack->trackLength = trackLength;

	pNewTrack->next = NULL;
	pNewTrack->prev = NULL;

	if(listPtr->head == NULL && listPtr->tail == NULL && listPtr->curr == NULL) {
		listPtr->head = pNewTrack;
		listPtr->tail = pNewTrack;
		listPtr->curr = pNewTrack;
	} else if (listPtr->curr == listPtr->head && listPtr->curr->prev == NULL) {
		pNewTrack->next = listPtr->curr;
		listPtr->curr->prev = pNewTrack;
		listPtr->head = pNewTrack;
	} else if (listPtr->head != listPtr->curr && listPtr->curr->prev != NULL) {
		pNewTrack->next = listPtr->curr;
		pNewTrack->prev = listPtr->curr->prev;
		listPtr->curr->prev->next = pNewTrack;
		listPtr->curr->prev = pNewTrack;
	} else {
		return INVALID_LIST_OPERATION;
	}

	return SUCCESS;
}

/* Add a new MP3 track into the playlist immediately
   AFTER the current position in the list */
int insertAfterCurr(Playlist* listPtr, char trackName[], int trackLength) {
	
	if (listPtr == NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	if (trackName == 0) {
		return INVALID_INPUT_PARAMETER;
	}

	if (strlen(trackName) > 49 || strlen(trackName) < 1) {
		return INVALID_INPUT_PARAMETER;
	}

	if (trackLength < 1) {
		return INVALID_INPUT_PARAMETER;
	}

	MP3Track *pNewTrack;
	pNewTrack = (MP3Track*)myMalloc(sizeof(MP3Track));

	if (pNewTrack == NULL) {
		return MEMORY_ALLOCATION_ERROR;
	}

	strcpy(pNewTrack->trackName, trackName)
	pNewTrack->trackLength = trackLength;

	pNewTrack->next = NULL;
	pNewTrack->prev = NULL;

	if(listPtr->head == NULL && listPtr->tail == NULL && listPtr->curr == NULL) {
		listPtr->head = pNewTrack;
		listPtr->tail = pNewTrack;
		listPtr->curr = pNewTrack;
	} else if (listPtr->curr == listPtr->tail && listPtr->curr->next == NULL) {
		pNewTrack->prev = listPtr->curr;
		listPtr->curr->next = pNewTrack;
		listPtr->tail = pNewTrack;
	} else if (listPtr->tail != listPtr->curr && list->curr->next != NULL) {
		pNewTrack->prev = listPtr->curr;
		pNewTrack->next = listPtr->curr->next;
		listPtr->curr->next->prev = pNewTrack;
		listPtr->curr->next = pNewTrack;
	} else {
		return INVALID_LIST_OPERATION;
	}

	return SUCCESS;
}

/* Skip to the next track in the playlist, i.e. shift 'curr' one
   position forward in the list */
int skipNext(Playlist* listPtr) {
	
	if (listPtr == NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	if (listPtr->head == NULL && listPtr->tail == NULL && listPtr->curr == NULL) {
		return INVALID_LIST_OPERATION;
	} else if (listPtr->head == listPtr->tail == listPtr->curr) {
		return INVALID_LIST_OPERATION;
	} else if (listPtr->curr->next == NULL) {
		return INVALID_LIST_OPERATION;
	} else {
		listPtr->curr = listPtr->curr->next;
	}

	return SUCCESS;
}

/* Skip to the previous track in the playlist, i.e. shift 'curr' one
   position back in the list */
int skipPrev(Playlist* listPtr) {

	if (listPtr == NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	if (listPtr->head == NULL && listPtr->tail == NULL && listPtr->curr == NULL) {
		return INVALID_LIST_OPERATION;
	} else if (listPtr->head == listPtr->tail == listPtr->curr) {
		return INVALID_LIST_OPERATION;
	} else if (listPtr->curr->prev == NULL) {
		return INVALID_LIST_OPERATION;
	} else {
		listPtr->curr = listPtr->curr->prev;
	}

	return SUCCESS;
}

/* Get the data for the current track in the playlist */
int getCurrentTrack(Playlist* listPtr, MP3Track *pTrack) {

	if (listPtr == NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	if (pTrack == NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	if (listPtr->head == NULL && listPtr->tail == NULL && listPtr->curr == NULL) {
		return INVALID_LIST_OPERATION;
	} else {
		MP3Track *pTempTrack = listPtr->curr;

		strcpy(pTrack->trackName, pTempTrack->trackName);
		pTrack->trackLength = pTempTrack->trackLength;

		free(pTempTrack);
	}

	return SUCCESS;
}

/* Remove the MP3 track from the current position in the list. The track data should be copied into 
   the variable provided (*pTrack) for confirmation. The variable â€˜moveForwardâ€™ is used to suggest 
   what happens to the â€˜currâ€™ pointer in the list after the track is removed. If â€˜moveForwardâ€™ is set 
   to 1 then the â€˜currâ€™ pointer should be set to point to the next track in the list, immediately 
   after the one which has just been removed. Otherwise, â€˜currâ€™ should be set to point to the previous 
   track in the list, immediately prior to the one which has just been removed. */
int removeAtCurr(Playlist* listPtr, MP3Track *pTrack, int moveForward) {

	if (listPtr == NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	if (pTrack == NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	if (moveForward == NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	if (listPtr->head == NULL && listPtr->tail == NULL && listPtr->curr == NULL) {
		return INVALID_LIST_OPERATION;
	} else if (listPtr->head == listPtr->tail == listPtr->curr) {
		pTrack = listPtr->curr;
		listPtr->head = NULL;
		listPtr->tail = NULL;
		listPtr->curr = NULL;
		free(pTrack);
	} else if (listPtr->head == listPtr->curr) {
		pTrack = listPtr->curr;
		listPtr->head = pTrack->next;
		listPtr->head->prev = NULL;
		listPtr->curr = listPtr->head;
		free(pTrack);
	} else if (listPtr->tail == listPtr->curr) {
		pTrack = listPtr->curr;
		listPtr->tail = pTrack->prev;
		listPtr->tail->next = NULL;
		listPtr->curr = listPtr->tail;
		free(pTrack);
	} else if (listPtr->curr != listPtr->head && listPtr->curr != listPtr->tail) {
		pTrack = listPtr->curr;
		pTrack->prev->next = pTrack->next;
		pTrack->next->prev = pTrack->prev;

		if (moveForward == 1) {
			listPtr->curr = pTrack->next;
		} else {
			listPtr->curr = pTrack->prev;
		}
		free(pTrack);
	}

	return SUCCESS;
}

/* Empty the entire contents of the playlist, freeing up any memory that it currently uses */
int clearPlaylist(Playlist* listPtr) {

	if (listPtr == NULL) {
		return INVALID_INPUT_PARAMETER
	}

	if (listPtr->head == NULL && listPtr->tail == NULL && listPtr->curr == NULL) {
		return SUCCESS
	}

	while (listPtr->head != NULL) {
		MP3Track *currentHead = listPtr->head;

		listPtr->head = listPtr->head->next;

		free(currentHead);
	}

	listPtr->head = NULL;
	listPtr->tail = NULL;
	listPtr->curr = NULL;

	free(listPtr);

	return SUCCESS;
}

/* save details of all of the tracks in the playlist into the given file */
int savePlaylist(Playlist *listPtr, char filename[]) {
	
	if (listPtr == NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	if (filename == 0) {
		return INVALID_INPUT_PARAMETER;

	Playlist *tempListPtr;
	tempListPtr = (Playlist*)myMalloc(sizeof(Playlist));

	if (tempListPtr == NULL) {
		return MEMORY_ALLOCATION_ERROR;
	}


	FILE *fp;
	fp = fopen(filename, "w")
	
	if (fp != NULL) {
		while (tempListPtr->head !=NULL) {
			fputs(templistPtr->trackName, fp);
			fprintf(fp, "#");
			fprintf(fp, "%d", tempListPtr->trackLength);
			fprintf(fp, "#");
			fprintf(fp, "\n");
			tempListPtr->head = tempListPtr->head->next;
		}
		fclose(fp);
	}

	free(tempListPtr);
	return SUCCESS;
}

/* This function is similar to 'createPlaylist'. It should create a new, empty playlist BUT
   then also load the details of a playlist from the given file (a list of track names and 
   track lengths); insert these as new MP3 tracks into your playlist, and store a pointer to 
   the newly created playlist into the variable provided (e.g. listPtr)  */
int loadPlaylist(Playlist **listPtr, char filename[]) {
	return NOT_IMPLEMENTED;
}