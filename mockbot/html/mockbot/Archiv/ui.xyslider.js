/*
 * XY Slider for jQuery UI
 *
 * Copyright 2011, Arnout Bosboom
 * 
 * Dual licensed under the MIT or GPL Version 3 licenses.
 * http://www.gnu.org/copyleft/gpl.html
 * http://www.opensource.org/licenses/MIT
 * 
 * Project page:
 * http://sourceforge.net/projects/xyslider
 *
 * Depends:
 * jquery
 * jquery.ui.core.js
 * jquery.ui.mouse.js
 * jquery.ui.widget.js
 */

(function($) {
$.widget('ui.xyslider', $.ui.mouse, {
	options: {
		x:0,
		y:0,
		minX:0,
		maxX:100,
		minY:0,
		maxY:100,
		stepX:1,
		stepY:1,
	},
	
	_create:function() {
		var	o = this.options,
			e = this.element;
		this._mouseInit();
		e.addClass('ui-xyslider');
		this._x = ($('<div></div>'))
			.appendTo(e)
			.addClass('ui-xyslider-x')
			.css({	
					position:'absolute',
					top:'0px',
					left:'0px',
					height:e.innerHeight()+'px', 
					width:'0px'
			});
		
		this._y = ($('<div></div>'))
			.appendTo(e)
			.addClass('ui-xyslider-y')
			.css({
					position:'absolute',
					top:'0px',
					left:'0px',
					height:'0px',
					width:e.innerWidth()+'px'
			});
		
		this._rangeX = (o.maxX - o.minX) / o.stepX;
		this._rangeY = (o.maxY - o.minY) / o.stepY;
		this.value({x:o.x, y:o.y});
	},

	destroy:function() {
		this.element.removeClass('ui-xyslider');
		this._x.remove();
		this._y.remove();
		this._mouseDestroy();
		$.Widget.prototype.destroy.apply(this);
	},
	
	value:function(values) {
		var	o = this.options,
			e = this.element;
		
		// setter : value to coordinate
		if(arguments.length) {
			var	Cx = (e.innerWidth() / this._rangeX) * (((Math.min(Math.max(values.x, o.minX), o.maxX)) - o.minX) / o.stepX),
				Cy = (e.innerHeight() / this._rangeY) * (((Math.min(Math.max(values.y, o.minY), o.maxY)) - o.minY) / o.stepY);
			
			this._refresh(Cx,Cy);
			this._trigger('change', null, this.value());
		}
		
		// getter : coordinate to value
		else {
			var	Vx = o.minX + (o.stepX * (Math.round((this._rangeX / e.innerWidth()) * this._x.width()))),
				Vy = o.minY + (o.stepY * (Math.round((this._rangeY / e.innerHeight()) * this._y.height())));
	
			return {x:Vx, y:Vy}	
		}
	},
	
	_refresh:function(Cx,Cy) {
		this._y.css('top', this.element.innerHeight() - Cy);
		this._y.height(Cy);
		this._x.width(Cx);
	},
	
	_mouseStart: function(event) {
		this._trigger('start', event, this.value());
		return true;
	},

	_mouseDrag: function(event) {
		var	offset = this.element.offset(),
			Cx = event.pageX - offset.left,
			Cy = this.element.innerHeight() - (event.pageY - offset.top);
		
		if(Cx <0 || Cx > this.element.innerWidth() || Cy < 0 || Cy > this.element.innerHeight()) {
			return false;
		}
		
		this._refresh(Cx,Cy);
		this._trigger('slide', event, this.value());
	},
	
	_mouseStop: function(event) {
		var values = this.value();
		this._trigger('stop', event, values);
		this._trigger('change', event, values);
	},
	
	_mouseCapture: function(event) {
		var	offset = this.element.offset(),
			values = this.value(),
			Cx = event.pageX - offset.left,
			Cy = this.element.innerHeight() - (event.pageY - offset.top);
		
		if((this.options.disabled) || (Cx <0 || Cx > this.element.innerWidth() || Cy < 0 || Cy > this.element.innerHeight())) {
			return false;
		}
		
		this._refresh(Cx, Cy);
		this._trigger('slide', event, values);
		this._trigger('change', event, values);
		return true;
	}
}
)})(jQuery);