/*
 * CREATE USER adds a login user. PASSWORD sets the credential; without it
 * the user authenticates by trust.
 */
CreateUserStmt:
			CREATE_P USER ColId opt_user_password
				{
					PGCreateUserStmt *n = makeNode(PGCreateUserStmt);
					n->user = $3;
					n->password = $4;
					$$ = (PGNode *)n;
				}
		;

opt_user_password:
	PASSWORD Sconst				{ $$ = $2; }
	| /* empty */				{ $$ = NULL; }
