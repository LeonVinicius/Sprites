#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>

#define FRAME_WIDTH 44   
#define FRAME_HEIGHT 48  
#define NUM_FRAMES 4     
#define FRAME_DURATION 0.2 

int main() {
    al_init();
    al_install_keyboard();
    al_init_image_addon();

    ALLEGRO_DISPLAY* disp = al_create_display(600, 400);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue();

    
    bool sair = false;
    int tecla = 0;
    float x = 30;         
    float y = 270;        
    int current_frame = 0; 
    float frame_time = 30/100;  
    float frame = 0;
  

   
    ALLEGRO_BITMAP* imagem = al_load_bitmap("C:/Users/Leon/source/repos/JogoEmAllegro/JogoEmAllegro/BG.jpg");
    ALLEGRO_BITMAP* Personagem = al_load_bitmap("C:/Users/Leon/source/repos/JogoEmAllegro/JogoEmAllegro/Walking.png");
   

    
    al_register_event_source(fila_eventos, al_get_display_event_source(disp));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));

    al_start_timer(timer); 

    
    while (!sair) {
        ALLEGRO_EVENT evento;
        al_wait_for_event(fila_eventos, &evento);

        
        if (evento.type == ALLEGRO_EVENT_TIMER) {
           
           


            al_draw_scaled_bitmap(imagem, 0, 0, 600, 400, 0, 0, 600, 400, 0);

            frame += 0.3;
                if ((int)frame >= NUM_FRAMES) {
                    frame = 0;
                }

            
            al_draw_scaled_bitmap(Personagem, ((int)frame) * FRAME_WIDTH, 0, FRAME_WIDTH, FRAME_HEIGHT, x, y, 100,100,0);

            al_flip_display();
        }
        else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
 
            switch (evento.keyboard.keycode) {
            case ALLEGRO_KEY_LEFT:
                x -= 3;
                break;

            case ALLEGRO_KEY_RIGHT:
                x += 3;
                break;
            }
        }
        else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            sair = true;
        }
    }


    al_destroy_bitmap(Personagem);
    al_destroy_bitmap(imagem);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(fila_eventos);

    return 0;
}
