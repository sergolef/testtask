<?php
if(isset($car))
{
    echo render(field_view_field('car', $car, 'car_image', array('settings' => array('image_style'=>'medium'))));
}
?> 

