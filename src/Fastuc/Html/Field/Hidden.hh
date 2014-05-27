<?hh // strict
namespace Fastuc\Html\Field;

class Hidden extends \Fastuc\Html\Field
{
	public function __construct( $name, $value = '' )
	{
		$this->name = $name;
		$this->value = $value;
	}

	public function __toString()
	{
		return sprintf('<input id="%s" type="hidden" name="%s" value="%s" />',
				$this->name, $this->name, $this->value);
	}
}


