enum node_kind {ID_NODE,INT_NODE,LPRP_NODE,PLUS_NODE,MINUS_NODE,STAR_NODE,DIV_NODE,UMINUS_NODE};

typedef struct Exp {
	enum node_kind kind;
	union {
		char type_id[33];             //�ɱ�ʶ�����ɵ�exp���
		int type_int;            //�ɳ������ɵ�exp���
		struct {
			struct Exp *pExp1;
			struct Exp *pExp2;
			}ptr;              //���������ɵ�exp���
	};
} *PEXP;


