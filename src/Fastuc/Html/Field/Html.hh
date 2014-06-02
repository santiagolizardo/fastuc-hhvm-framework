<?hh // strict
namespace Fastuc\Html\Field;

class Html extends \Fastuc\Html\Field
{
	public function __construct($value)
	{
		$this->value = $value;
	}

	public function __toString()
	{
		return $this->value;
	}
}

