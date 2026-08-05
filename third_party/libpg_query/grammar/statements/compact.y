/*
 * The COMPACT statement merges a table's small files into target-sized ones.
 * FINAL keeps sweeping until a pass merges nothing.
 */
CompactStmt:
			COMPACT qualified_name opt_final
				{
					PGCompactStmt *n = makeNode(PGCompactStmt);
					n->relation = $2;
					n->final = $3;
					$$ = (PGNode *)n;
				}
		;

opt_final:
	FINAL 						{ $$ = true; }
	| /* empty */ 				{ $$ = false; }
