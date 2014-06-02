<?hh // strict
namespace Fastuc\Html\Field;

class Radio extends \Fastuc\Html\Field
{
	private $checked;

	public function __construct( $name, $value = '' )
	{
		$this->name = $name;
		$this->value = $value;
	}

	public function setLabel( $label )
	{
		$this->label = $label;
	}

	public function setChecked( $checked )
	{
		$this->checked = $checked;
	}

	public function __toString()
	{
		$checked = $this->checked ? ' checked="checked"' : '';
		return sprintf('<input id="%s" type="radio" name="%s" value="%s" %s/> <label for="">%s</label>',
				$this->name, $this->name, $this->value, $checked, $this->label);
	}
}

