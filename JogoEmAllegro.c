#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>

#define FRAME_WIDTH 44   
#define FRAME_HEIGHT 48  
#define NUM_FRAMES 4     
#define FRAME_DURATION 0.2 
#define JUMP_HEIGHT 80  
#define GRAVITY 4     

int fase_atual = 0; 
bool menu_aberto = false;

void desenhar_menu(ALLEGRO_FONT* fonte) {
    al_clear_to_color(al_map_rgb(0, 0, 0));

  
    al_draw_text(fonte, al_map_rgb(255, 255, 255), 400, 200, ALLEGRO_ALIGN_CENTER, "1. Fase 1");
    al_draw_text(fonte, al_map_rgb(255, 255, 255), 400, 250, ALLEGRO_ALIGN_CENTER, "2. Fase 2");
    al_draw_text(fonte, al_map_rgb(255, 255, 255), 400, 300, ALLEGRO_ALIGN_CENTER, "3. Fase 3");
    al_draw_text(fonte, al_map_rgb(255, 255, 255), 400, 350, ALLEGRO_ALIGN_CENTER, "4. Voltar para casa");

    al_flip_display();
}

int main() {
    al_init();
    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    ALLEGRO_FONT* fonte = al_create_builtin_font(); 

    ALLEGRO_DISPLAY* disp = al_create_display(800, 600);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue();

    bool sair = false;
    bool on_homepage = true;
    float x = 30;
    float y = 435;
    float frame = 0;

    bool pulando = false;
    float jump_speed = 0;
    float jump_start_y = y;

    bool andando_esquerda = false;
    bool andando_direita = false;
    bool parado = true;

    ALLEGRO_BITMAP* casa = al_load_bitmap("C:/Users/Leon/source/repos/JogoEmAllegro/JogoEmAllegro/casa.png");
    ALLEGRO_BITMAP* Personagem = al_load_bitmap("C:/Users/Leon/source/repos/JogoEmAllegro/JogoEmAllegro/Walking.png");
    ALLEGRO_BITMAP* Pulando = al_load_bitmap("C:/Users/Leon/source/repos/JogoEmAllegro/JogoEmAllegro/Pulando.png");
    ALLEGRO_BITMAP* Parado = al_load_bitmap("C:/Users/Leon/source/repos/JogoEmAllegro/JogoEmAllegro/PGParado.png");
    ALLEGRO_BITMAP* AndandoESQ = al_load_bitmap("C:/Users/Leon/source/repos/JogoEmAllegro/JogoEmAllegro/WalkingLeft.png");
    ALLEGRO_BITMAP* Homepage = al_load_bitmap("C:/Users/Leon/source/repos/JogoEmAllegro/JogoEmAllegro/bg2.jpg");
    ALLEGRO_BITMAP* cenario1 = al_load_bitmap("C:/Users/Leon/source/repos/JogoEmAllegro/JogoEmAllegro/cenario1.png");
    ALLEGRO_BITMAP* cenario2 = al_load_bitmap("C:/Users/Leon/source/repos/JogoEmAllegro/JogoEmAllegro/cenario2.png");
    ALLEGRO_BITMAP* cenario3 = al_load_bitmap("C:/Users/Leon/source/repos/JogoEmAllegro/JogoEmAllegro/cenario3.png");

    al_register_event_source(fila_eventos, al_get_display_event_source(disp));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));

    al_start_timer(timer);

    while (!sair) {
        ALLEGRO_EVENT evento;
        al_wait_for_event(fila_eventos, &evento);

        if (evento.type == ALLEGRO_EVENT_TIMER) {

            if (on_homepage) {
               
                al_draw_scaled_bitmap(Homepage, 0, 0, al_get_bitmap_width(Homepage), al_get_bitmap_height(Homepage), 0, 0, 800, 600, 0);
                al_flip_display();
            }
            else if (menu_aberto) {
                desenhar_menu(fonte);
            }
            else {
               
                ALLEGRO_BITMAP* cenario_atual;
                if (fase_atual == 1) {
                    cenario_atual = cenario1;
                }
                else if (fase_atual == 2) {
                    cenario_atual = cenario2;
                }
                else if (fase_atual == 3) {
                    cenario_atual = cenario3;
                }
                else {
                    cenario_atual = casa; 
                }

                al_draw_scaled_bitmap(cenario_atual, 0, 0, al_get_bitmap_width(cenario_atual), al_get_bitmap_height(cenario_atual), 0, 0, 800, 600, 0);

               
                if (andando_esquerda) {
                    x -= 3;
                    parado = false;
                }
                if (andando_direita) {
                    x += 3;
                    parado = false;
                }

                if (!andando_esquerda && !andando_direita && !pulando) {
                    parado = true;
                }

                if (pulando) {
                    y -= jump_speed;
                    jump_speed -= GRAVITY * 0.1;

                    if (y >= jump_start_y) {
                        y = jump_start_y;
                        pulando = false;
                        jump_speed = 0;
                    }
                }

                
                frame += 0.3;
                if ((int)frame >= NUM_FRAMES) {
                    frame = 0;
                }

                if (pulando) {
                    al_draw_scaled_bitmap(Pulando, ((int)frame) * FRAME_WIDTH, 0, FRAME_WIDTH, FRAME_HEIGHT, x, y, 100, 100, 0);
                }
                else if (parado) {
                    al_draw_scaled_bitmap(Parado, 0, 0, FRAME_WIDTH, FRAME_HEIGHT, x, y, 100, 100, 0);
                }
                else if (andando_esquerda) {
                    al_draw_scaled_bitmap(AndandoESQ, ((int)frame) * FRAME_WIDTH, 0, FRAME_WIDTH, FRAME_HEIGHT, x, y, 100, 100, 0);
                }
                else if (andando_direita) {
                    al_draw_scaled_bitmap(Personagem, ((int)frame) * FRAME_WIDTH, 0, FRAME_WIDTH, FRAME_HEIGHT, x, y, 100, 100, 0);
                }

                al_flip_display();
            }
        }
        else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (on_homepage && evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                on_homepage = false;
            }
            else if (!on_homepage) {
                switch (evento.keyboard.keycode) {
                case ALLEGRO_KEY_LEFT:
                    andando_esquerda = true;
                    parado = false;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    andando_direita = true;
                    parado = false;
                    break;

                case ALLEGRO_KEY_UP:
                    if (!pulando) {
                        pulando = true;
                        jump_speed = 10;
                        jump_start_y = y;
                    }
                    break;

                case ALLEGRO_KEY_ESCAPE:
                    
                    menu_aberto = !menu_aberto;
                    break;

                case ALLEGRO_KEY_1:
                    if (menu_aberto) {
                        fase_atual = 1; 
                        menu_aberto = false;
                    }
                    break;

                case ALLEGRO_KEY_2:
                    if (menu_aberto) {
                        fase_atual = 2; 
                        menu_aberto = false;
                    }
                    break;

                case ALLEGRO_KEY_3:
                    if (menu_aberto) {
                        fase_atual = 3;
                        menu_aberto = false;
                    }
                    break;

                case ALLEGRO_KEY_4:
                    if (menu_aberto) {
                        fase_atual = 0; 
                    }
                    break;
                }
            }
        }
        else if (evento.type == ALLEGRO_EVENT_KEY_UP) {
            switch (evento.keyboard.keycode) {
            case ALLEGRO_KEY_LEFT:
                andando_esquerda = false;
                break;

            case ALLEGRO_KEY_RIGHT:
                andando_direita = false;
                break;
            }
        }
        else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            sair = true;
        }
    }

   
    al_destroy_bitmap(Personagem);
    al_destroy_bitmap(casa);
    al_destroy_bitmap(Homepage);
    al_destroy_bitmap(cenario1);
    al_destroy_bitmap(cenario2);
    al_destroy_bitmap(cenario3);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(fila_eventos);
    al_destroy_font(fonte);

    return 0;
}
