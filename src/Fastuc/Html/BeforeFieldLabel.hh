<?hh // strict
namespace Fastuc\Html;

class BeforeFieldLabel extends \Fastuc\Html\FieldLabel
{
	/**
	 * @return string
	 */
	public function toHtml()
	{
		$html = sprintf( '<label for="%s">%s</label>%s', $this->field->getId(), $this->labelText, $this->field );
		return $html;
	}
}


