# Compiler used
CC=gcc

# Flags to use when compiling
CFLAGS=-Wall -g -Iinclude `pkg-config --cflags glib-2.0`

# Flags to use when linking
LDFLAGS=`pkg-config --libs glib-2.0` -lm

programa-principal: src/main.o src/data_manager.o src/uteis.o src/estatisticas.o src/user.o src/user_manager.o src/albuns.o src/albuns_manager.o src/historico.o src/historico_manager.o src/artist.o src/artist_manager.o src/music.o src/music_manager.o src/artist_info.o src/artist_info_manager.o src/parsing.o src/parsingInputs.o src/queries.o src/validation.o recomendador/recomendador-linux-x86_64.o src/limpeza.o src/discografia.o src/discografia_manager.o src/week.o src/week_manager.o src/escrita.o src/matrix.o src/matrix_manager.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

programa-testes: src/main_testes.o src/data_manager.o src/uteis.o src/estatisticas.o src/user.o src/user_manager.o src/albuns.o src/albuns_manager.o src/historico.o src/historico_manager.o src/artist.o src/artist_manager.o src/music.o  src/music_manager.o src/artist_info.o src/artist_info_manager.o src/parsing.o src/parsingInputs.o src/queries.o src/validation.o src/testes.o recomendador/recomendador-linux-x86_64.o  src/limpeza.o src/discografia.o src/discografia_manager.o src/week.o src/week_manager.o src/escrita.o src/matrix.o src/matrix_manager.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

programa-interativo: src/main_inter.o src/interface.o src/data_manager.o src/uteis.o src/estatisticas.o src/user.o src/user_manager.o src/albuns.o src/albuns_manager.o src/historico.o src/historico_manager.o src/artist.o src/artist_manager.o src/music.o  src/music_manager.o src/artist_info.o src/artist_info_manager.o src/parsing.o src/parsingInputs.o src/queries.o src/validation.o recomendador/recomendador-linux-x86_64.o  src/limpeza.o src/discografia.o src/discografia_manager.o src/week.o src/week_manager.o src/escrita.o src/matrix.o src/matrix_manager.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@


src/escrita.o: src/escrita.c
	$(CC) $(CFLAGS) -c $< -o $@

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/main_testes.o: src/main_testes.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/main_inter.o: src/main_inter.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/data_manager.o: src/data_manager.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/user.o: src/user.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/user_manager.o: src/user_manager.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/albuns.o: src/albuns.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/albuns_manager.o: src/albuns_manager.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/historico.o: src/historico.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/historico_manager.o: src/historico_manager.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/uteis.o: src/uteis.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/estatisticas.o: src/estatisticas.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/artist.o: src/artist.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/artist_manager.o: src/artist_manager.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/music.o: src/music.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/music_manager.o: src/music_manager.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/discografia.o: src/discografia.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/discografia_manager.o: src/discografia_manager.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/week.o: src/week.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/week_manager.o: src/week_manager.c
	$(CC) $(CFLAGS) -c -o $@ $<


src/artist_info.o: src/artist_info.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/artist_info_manager.o: src/artist_info_manager.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/parsing.o: src/parsing.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/parsingInputs.o: src/parsingInputs.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/queries.o: src/queries.c 
	$(CC) $(CFLAGS) -c -o $@ $<

src/validation.o: src/validation.c 
	$(CC) $(CFLAGS) -c -o $@ $<

src/testes.o: src/testes.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/interface.o: src/interface.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/limpeza.o: src/limpeza.c
	$(CC) $(CFLAGS) -c -o $@ $<




debug: programa-principal
	gdb --args ./programa-principal dataset inputs-small.txt

valgrind: programa-principal
	valgrind -s --leak-check=full --track-origins=yes --show-leak-kinds=all ./programa-principal dataset inputs-small.txt

run: programa-principal
	./programa-principal dataset inputs-small.txt

teste-small: programa-testes
	./programa-testes dataset inputs-small.txt resultados-esperados

teste-big: programa-testes
	./programa-testes dataset inputs-big.txt resultados-esperados

interativo: programa-interativo
	./programa-interativo dataset inputs-small.txt

clean:
	-rm -f src/*.o resultados/*.txt resultados/*.csv