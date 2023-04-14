#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order;
	struct RecordType* next; 
};

// Fill out this structure
struct HashType
{
	struct RecordType* table;
};

// Compute the hash function
int hash(int x, int tableSize)
{
	return x % tableSize;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

//Function to insert record into the Hash table
void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
	
	int i = hash(record->id, tableSize);
	
	struct HashType *tempHash = &hashTable[i];

	if(tempHash->table == NULL)
	{
		tempHash->table = record;
		record->next = NULL;
	}
	else
	{
		struct RecordType* current = tempHash->table;
		while(current->next != NULL)
		{
			current = current->next;
		}
		
		current->next = record;
		record->next = NULL;
		
	}
	
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;
	struct RecordType* current;
	for (i=0;i<hashSz;++i)
	{
		// if index is occupied with any records, print all
		if(pHashArray[i].table != NULL)
		{
			printf("Index %d -> ", i);
			current = pHashArray[i].table;

			while(current != NULL)
			{
				printf("%d, %c, %d -> ", current->id, current->name, current->order);
				current = current->next;
			}
			printf("NULL\n");
		}
	}
	
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;
	int hashTableSize = 11;
	int i;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
	struct HashType *hashTable = (struct HashType*) calloc(hashTableSize, sizeof(struct HashType));

	if(hashTable == NULL)
	{
		printf("Memory failed to allocate");
		exit(-1);
	}

	for(i = 0; i < recordSz; i++)
	{
		insertRecord(hashTable, pRecords + i, hashTableSize);
	}

	displayRecordsInHash(hashTable, hashTableSize);

	//free allocated memory
	free(pRecords);
	free(hashTable);

	return 0;
}