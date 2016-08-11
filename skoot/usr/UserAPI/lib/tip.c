/*
**	/usr/UserAPI/lib/tip.c
**
**	Copyright Skotos Tech Inc 1999, 2004.
*/

mapping last_tip_seen;
mapping seen_all;

static
void create() {
   last_tip_seen = ([ ]);   /* ie sword2 */
   seen_all = ([ ]);
}

string tipclear() {
   last_tip_seen = ([ ]);
   seen_all = ([ ]);

   return "tips cleared";
}

int next_tip_id(string topic) {
   return last_tip_seen[topic] ? last_tip_seen[topic] + 1 : 1;
}

void set_last_tip_seen(string topic, int tip_num) {
   last_tip_seen[topic] = tip_num;
}

void set_seen_all(string topic, int highval) {
   seen_all[topic] = highval;		
}

int query_seen_all(string topic) {
   return seen_all[topic] ? seen_all[ topic ] : 0;
}
