//
//  comparator.h
//  
//
//  Created by Grace Benway on 3/8/17.
//
//

#ifndef comparator_h
#define comparator_h

typedef int (*Comparator)(void*,void*);
typedef void (*Printer)(FILE*,void*);

extern int intComparator(void *p, void *q);
extern int realComparator(void *p, void *q);
extern int stringComparator(void *p, void *q);

#endif /* comparator_h */


