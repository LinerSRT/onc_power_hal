#ifndef __POWERHINTPARSER__
#define __POWERHINTPARSER__

#define POWERHINT_XML      "/vendor/etc/powerhint.xml"
#define MAX_HINT 6
#define MAX_PARAM 30

typedef struct perflock_param_t {
    int type;
    int numParams;
    int paramList[MAX_PARAM];//static limit on number of hints - 15
}perflock_param_t;

static perflock_param_t powerhint[MAX_HINT];

int parsePowerhintXML();
int *getPowerhint(int, int*);

#endif /* __POWERHINTPARSER__ */
