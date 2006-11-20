#ifndef _FRIEND_H_
#define _FRIEND_H_

struct map_session_data;

void do_init_friend(void);
void do_final_friend(void);

int friend_add_request( struct map_session_data *sd, char* name );
int friend_add_reply( struct map_session_data *sd, int account_id, int char_id, int flag );
int friend_del_request( struct map_session_data *sd, int account_id, int char_id );
int friend_del_from_otherserver( int account_id, int char_id, int account_id2, int char_id2 );

int friend_send_info( struct map_session_data *sd );
int friend_send_online( struct map_session_data *sd, int flag );
int friend_send_online_from_otherserver( int account_id, int char_id, int flag, int num, int* list );

#endif
