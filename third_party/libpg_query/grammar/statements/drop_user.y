/*
 * DROP USER removes a login user.
 */
DropUserStmt:
			DROP USER ColId
				{
					PGDropUserStmt *n = makeNode(PGDropUserStmt);
					n->user = $3;
					$$ = (PGNode *)n;
				}
		;
